# External ROS message fetch

`tools/fetch.py` stages selected ROS `msg/*.msg` definitions for the existing
Hakoniwa PDU generation pipeline. External Git repositories are temporary input;
their checkouts are not copied into or retained by this repository.

## Boundary

The fetch layer owns only:

1. resolving one declared Git source;
2. locating selected ROS packages by `package.xml`;
3. copying each package's direct `msg/*.msg` files;
4. recording deterministic source and file provenance.

It does not resolve transitive message dependencies, build ROS packages, or
decide which generated PDU artifacts are committed. The separate host-side
`tools/generate_from_sources.py` command connects this fetch boundary to the
existing generator.

## Source manifest

```yaml
schema_version: 1

source:
  type: git
  repository: https://github.com/ros-drivers/ackermann_msgs.git
  ref: df2fe51eb04e8bd3c0ba4f8a6ded8aea3815b660

packages:
  - ackermann_msgs
```

Use a full commit SHA for reproducible inputs. Branches and tags are accepted by
Git, but the sample manifests committed to this registry should be pinned. The
resolved commit is always written to the output provenance.

## Usage

Install the small YAML dependency if it is not already available. The Business
Pack Foundation Python environment already provides it.

```bash
python3 -m pip install -r tools/requirements-fetch.txt
```

Fetch into the default `output_msgs/` directory:

```bash
python3 tools/fetch.py --sources sources/ackermann_msgs.yaml
```

Choose another output directory, such as a CI workspace:

```bash
python3 tools/fetch.py \
  --sources sources/ackermann_msgs.yaml \
  --output /tmp/hakoniwa-msgs
```

An existing selected package is never overwritten implicitly. Use `--clean` to
replace only package directories named in the source manifest:

```bash
python3 tools/fetch.py \
  --sources sources/ackermann_msgs.yaml \
  --output output_msgs \
  --clean
```

Unrelated output directories and files are preserved. The source is fetched and
validated before an existing selected package is replaced.

## Output contract

```text
output_msgs/
└── ackermann_msgs/
    ├── msg/
    │   ├── AckermannDrive.msg
    │   └── AckermannDriveStamped.msg
    └── source-manifest.json
```

`source-manifest.json` records:

- repository URL;
- requested ref and resolved 40-character commit SHA;
- package name, version, and licenses declared by `package.xml`;
- source package location in the external repository;
- SHA-256 for every copied message definition.

No local paths or timestamps are recorded, so identical source input produces an
identical provenance file.

## Licensing and dependencies

The provenance reports license text declared by `package.xml`; it does not infer
an SPDX identifier or replace legal review. If fetched definitions or derived
artifacts are redistributed, follow the upstream license and attribution terms.

Fetch copies only direct message definitions. For example,
`AckermannDriveStamped.msg` references `std_msgs/Header`; the downstream PDU
generator must already have `std_msgs` available through its normal search roots,
or a separate pinned source manifest must fetch that package.

## Selective PDU generation from the host

Do not add one-off external types to the large `config/ros_msgs.txt`. Select the
types to generate on the command line:

```bash
python3 tools/generate_from_sources.py \
  --sources sources/ackermann_msgs.yaml \
  ackermann_msgs/AckermannDrive
```

Multiple types and source manifests may be specified:

```bash
python3 tools/generate_from_sources.py \
  --sources sources/ackermann_msgs.yaml \
  ackermann_msgs/AckermannDrive \
  ackermann_msgs/AckermannDriveStamped
```

The host command performs the following reproducible sequence:

1. fetches each pinned source into ignored `output_msgs/`;
2. writes a temporary message list containing only the requested types;
3. writes a temporary search-path file that adds `output_msgs/` to the standard
   ROS and local IDL roots;
4. runs the existing generator through the pinned Docker image with
   `--incremental`;
5. removes the temporary configuration files.

The two tracked global configuration files remain unchanged. The dependency
resolver still includes types that are semantically required by a selection.
For example, selecting `AckermannDriveStamped` also resolves
`AckermannDrive` and `std_msgs/Header`; it does not pull in unrelated entries
from `config/ros_msgs.txt`.

The default output is the tracked `pdu/` tree. For a smoke test, direct output
to an ignored repository-relative directory:

```bash
python3 tools/generate_from_sources.py \
  --sources sources/ackermann_msgs.yaml \
  --output-dir .cache/ackermann-pdu-smoke \
  ackermann_msgs/AckermannDrive
```

The output path must stay inside the repository because Docker only mounts this
workspace. `--cdr` selects the generator's CDR-only path.
