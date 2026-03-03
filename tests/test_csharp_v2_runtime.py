import subprocess
import unittest
from pathlib import Path


class CSharpV2RuntimeTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.repo_root = Path(__file__).resolve().parents[1]
        cls.project = cls.repo_root / "tests" / "csharp_v2_smoke" / "CSharpV2Smoke.csproj"

    def test_csharp_v2_smoke_roundtrip(self):
        result = subprocess.run(
            ["dotnet", "run", "--no-restore", "--project", str(self.project)],
            cwd=self.repo_root,
            capture_output=True,
            text=True,
            check=False,
        )
        self.assertEqual(
            result.returncode,
            0,
            msg=f"dotnet run failed\nstdout:\n{result.stdout}\nstderr:\n{result.stderr}",
        )


if __name__ == "__main__":
    unittest.main()
