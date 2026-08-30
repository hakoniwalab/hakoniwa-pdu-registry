#!/usr/bin/env python3
from __future__ import annotations

import importlib.util
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from generators.generate_hako_pdu_msgs.dependency_resolver import DependencyResolver


TOOL_PATH = Path(__file__).resolve().parents[1] / "tools" / "fetch.py"
SPEC = importlib.util.spec_from_file_location("hakoniwa_pdu_fetch", TOOL_PATH)
assert SPEC is not None and SPEC.loader is not None
fetch_tool = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = fetch_tool
SPEC.loader.exec_module(fetch_tool)


class FetchToolTest(unittest.TestCase):
    def make_repository(self, root: Path) -> tuple[Path, str]:
        repository = root / "source repository"
        repository.mkdir()
        subprocess.run(["git", "init", "--quiet"], cwd=repository, check=True)
        subprocess.run(
            ["git", "config", "user.email", "fetch-test@example.invalid"],
            cwd=repository,
            check=True,
        )
        subprocess.run(
            ["git", "config", "user.name", "Fetch Test"],
            cwd=repository,
            check=True,
        )
        (repository / "msg").mkdir()
        (repository / "msg" / "Drive.msg").write_text(
            "float32 steering_angle\nfloat32 speed\n",
            encoding="utf-8",
        )
        (repository / "msg" / "DriveStamped.msg").write_text(
            "std_msgs/Header header\nDrive drive\n",
            encoding="utf-8",
        )
        (repository / "package.xml").write_text(
            "<?xml version=\"1.0\"?>\n"
            "<package format=\"3\">\n"
            "  <name>demo_msgs</name>\n"
            "  <version>1.2.3</version>\n"
            "  <license>BSD-3-Clause</license>\n"
            "</package>\n",
            encoding="utf-8",
        )
        subprocess.run(["git", "add", "."], cwd=repository, check=True)
        subprocess.run(
            ["git", "commit", "--quiet", "-m", "fixture"],
            cwd=repository,
            check=True,
        )
        commit = subprocess.run(
            ["git", "rev-parse", "HEAD"],
            cwd=repository,
            check=True,
            capture_output=True,
            text=True,
        ).stdout.strip()
        return repository, commit

    def write_manifest(
        self,
        root: Path,
        repository: Path,
        commit: str,
        package: str = "demo_msgs",
    ) -> Path:
        manifest = root / "source.yaml"
        manifest.write_text(
            "schema_version: 1\n"
            "source:\n"
            "  type: git\n"
            f"  repository: {json.dumps(str(repository))}\n"
            f"  ref: {commit}\n"
            "packages:\n"
            f"  - {package}\n",
            encoding="utf-8",
        )
        return manifest

    def test_fetches_only_messages_and_writes_deterministic_provenance(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            repository, commit = self.make_repository(root)
            manifest = self.write_manifest(root, repository, commit)
            first_output = root / "first"
            second_output = root / "second"

            fetch_tool.fetch_sources(sources=manifest, output=first_output)
            fetch_tool.fetch_sources(sources=manifest, output=second_output)

            package = first_output / "demo_msgs"
            self.assertEqual(
                [path.name for path in sorted((package / "msg").glob("*.msg"))],
                ["Drive.msg", "DriveStamped.msg"],
            )
            self.assertFalse((package / "package.xml").exists())
            provenance = json.loads(
                (package / "source-manifest.json").read_text(encoding="utf-8")
            )
            self.assertEqual(provenance["source"]["resolved_commit"], commit)
            self.assertEqual(provenance["package"]["version"], "1.2.3")
            self.assertEqual(
                provenance["package"]["declared_licenses"], ["BSD-3-Clause"]
            )
            self.assertEqual(
                (package / "source-manifest.json").read_bytes(),
                (second_output / "demo_msgs" / "source-manifest.json").read_bytes(),
            )

    def test_existing_output_requires_clean_and_clean_is_package_scoped(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            repository, commit = self.make_repository(root)
            manifest = self.write_manifest(root, repository, commit)
            output = root / "output"
            fetch_tool.fetch_sources(sources=manifest, output=output)
            (output / "demo_msgs" / "stale.txt").write_text("stale", encoding="utf-8")
            unrelated = output / "unrelated-package"
            unrelated.mkdir()
            (unrelated / "keep.txt").write_text("keep", encoding="utf-8")

            with self.assertRaisesRegex(fetch_tool.FetchError, "use --clean"):
                fetch_tool.fetch_sources(sources=manifest, output=output)

            fetch_tool.fetch_sources(sources=manifest, output=output, clean=True)
            self.assertFalse((output / "demo_msgs" / "stale.txt").exists())
            self.assertEqual(
                (unrelated / "keep.txt").read_text(encoding="utf-8"), "keep"
            )

    def test_missing_package_fails_without_partial_output(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            repository, commit = self.make_repository(root)
            manifest = self.write_manifest(root, repository, commit, "missing_msgs")
            output = root / "output"

            with self.assertRaisesRegex(fetch_tool.FetchError, "not found"):
                fetch_tool.fetch_sources(sources=manifest, output=output)

            self.assertEqual(list(output.iterdir()), [])

    def test_clean_preserves_existing_output_when_source_validation_fails(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            repository, commit = self.make_repository(root)
            manifest = self.write_manifest(root, repository, commit, "missing_msgs")
            existing = root / "output" / "missing_msgs"
            existing.mkdir(parents=True)
            marker = existing / "previous-output.txt"
            marker.write_text("keep on failure", encoding="utf-8")

            with self.assertRaisesRegex(fetch_tool.FetchError, "not found"):
                fetch_tool.fetch_sources(
                    sources=manifest,
                    output=root / "output",
                    clean=True,
                )

            self.assertEqual(marker.read_text(encoding="utf-8"), "keep on failure")

    def test_manifest_rejects_unsafe_package_name(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            repository, commit = self.make_repository(root)
            manifest = self.write_manifest(root, repository, commit, "../escape")

            with self.assertRaisesRegex(fetch_tool.FetchError, "invalid ROS package"):
                fetch_tool.load_source_manifest(manifest)

    def test_fetch_output_is_a_generator_search_root(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            repository, commit = self.make_repository(root)
            manifest = self.write_manifest(root, repository, commit)
            output = root / "output"
            fetch_tool.fetch_sources(sources=manifest, output=output)
            std_msgs = output / "std_msgs" / "msg"
            std_msgs.mkdir(parents=True)
            (std_msgs / "Header.msg").write_text(
                "builtin_interfaces/Time stamp\nstring frame_id\n", encoding="utf-8"
            )
            builtin = output / "builtin_interfaces" / "msg"
            builtin.mkdir(parents=True)
            (builtin / "Time.msg").write_text(
                "int32 sec\nuint32 nanosec\n", encoding="utf-8"
            )

            resolved = DependencyResolver([str(output)]).get_all_dependencies(
                ["demo_msgs/DriveStamped"]
            )

            self.assertEqual(
                set(resolved),
                {
                    "demo_msgs/DriveStamped",
                    "demo_msgs/Drive",
                    "std_msgs/Header",
                    "builtin_interfaces/Time",
                },
            )


if __name__ == "__main__":
    unittest.main()
