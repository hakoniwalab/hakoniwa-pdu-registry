# hakoniwa-pdu-registry

`hakoniwa-pdu-registry` defines the binary contract of Hakoniwa.
It is the single source of truth for PDU layouts, ensuring that every runtime,
tool, and bridge sees the same structure — reproducibly.

Generated PDUs are treated as long-lived assets rather than disposable outputs.

## Design Philosophy

`hakoniwa-pdu-registry` prioritizes deterministic binary layout stability
over conventional build-time generation workflows.

The source of truth in this project is not only the IDL definitions,
but the fully resolved, compiled, and offset-calculated binary layout
that is committed into the repository.

This design intentionally treats generated artifacts as part of the
binary contract, not as disposable build outputs.

Reproducibility across time, toolchains, and languages is considered
more critical than minimizing repository size or diff noise.

The committed artifacts are considered immutable historical records
of the binary contract at each revision.

## What it is

`hakoniwa-pdu-registry` is the authoritative place to define, generate, and manage Hakoniwa PDUs
(Protocol Data Units) derived from ROS 2 IDL (`.msg`) files.
It stores inputs, templates, and generated outputs so that PDU layouts stay stable across
runtimes and tools.
The registry is the single source of truth for Hakoniwa PDU layouts.

## Why this exists (Motivation)

ROS 2 `.msg` files are easy to author but do not guarantee:

- A canonical, language-agnostic memory layout
- Long-term management of generated outputs
- Reproducible binary compatibility across runtimes and tools

This registry addresses those gaps by versioning the definitions, templates, and generated
artifacts together and by enforcing a reproducible generation pipeline.

## What you get (Outputs / Artifacts)

Generated outputs are committed assets, not disposable byproducts.
Typical outputs include:

- C/C++ headers for PDU layouts and conversions under `pdu/types/`
- Python types and converters under `pdu/python/`
- JavaScript types and converters under `pdu/javascript/`
- C# types under `pdu/csharp/`
- Offset files under `pdu/offset/` and `pdu/offset_text/`
- Aligned size registry under `pdu/pdu_size/`

## Where to start

- Quickstart (Docker, reproducible): `README.md` below
- Message schema inputs: `idl/`
- Generator entrypoints: `generators/generate_hako_pdu_msgs/main.py`, `generators/generate_hako_service_msgs/main.py`
- Docker scripts: `docker/pull-image.bash`, `docker/run.bash`, `docker/create-image.bash`
- Message list and search paths: `config/ros_msgs.txt`, `config/search_path.txt`
- PDU binary format details: `docs/specs/pdu-binary-format.md`
- Docs index: `docs/README.md`

## Quickstart (Docker, reproducible)

This is the recommended way to generate PDUs with a pinned toolchain.

1. Pull (or build) the generator image.

```bash
bash docker/pull-image.bash
# or, if you want to build locally:
# bash docker/create-image.bash
```

2. Configure the target message list and search paths.

Edit `config/ros_msgs.txt` to list the ROS messages to convert.
Edit `config/search_path.txt` to point at ROS message definition roots.

3. Start the container.

```bash
bash docker/run.bash
```

4. Inside the container, run the generator.

```bash
cd /root/workspace/hakoniwa-pdu-registry
python3 -m generators.generate_hako_pdu_msgs.main config/ros_msgs.txt
```

5. Check the generated artifacts.

```text
pdu/types/
pdu/python/
pdu/javascript/
pdu/csharp/
pdu/offset/
pdu/offset_text/
pdu/pdu_size/
```

### Local run (non-reproducible, reference only)

If you must run outside Docker, ensure you have a compatible ROS 2 installation
and pass `--ros-root` so the generator can resolve standard message packages.
This mode is not guaranteed to be reproducible.

```bash
python3 -m generators.generate_hako_pdu_msgs.main config/ros_msgs.txt \
  --ros-root /path/to/your/ros2/install
```

## How it works (high-level)

```
ROS 2 IDL (.msg)
  -> Dependency resolution
  -> Code generation (C/C++/C#/Python/JS)
  -> Offset calculation (C compile)
  -> Converter generation (Python/JS)
  -> Size registry generation
  -> Committed PDU artifacts
```

## Repository layout

```
idl/            Input definitions (ROS 2 msg, generated service msg)
template/       Code generation templates
generators/     Python-based generators
pdu/            Generated PDU artifacts
config/         Message lists, search paths
docker/         Reproducible build environment
docs/           Specifications and guidance
```

## PDU format summary

PDUs serialize into:

```
[MetaData][BaseData][HeapData][ExtMeta planned]
```

Key rules (details in `docs/specs/pdu-binary-format.md`):

- `MetaData` is fixed-size and validated by `magicno` and `version`.
- `BaseData` is a C struct with fixed layout and references into `HeapData`.
- `HeapData` stores variable-length payloads referenced by offset/length.
- `epoch` is a generation tag and must only be compared for equality.
- Writers update `epoch` last as the commit marker.
- `ExtMeta` is planned and not implemented in this release.

## Generation workflow

1. Resolve dependencies from `config/ros_msgs.txt` using `config/search_path.txt`.
2. Generate multi-language type definitions into `pdu/`.
3. Calculate BaseData offsets by compiling a small C program.
4. Generate Python and JavaScript converters from the offset files.
5. Generate the PDU size registry under `pdu/pdu_size/`.

## Language support

### Python

Recommended for local use:

```bash
export PYTHONPATH=$PWD
```

Example:

```python
from pdu.python.geometry_msgs.pdu_pytype_Point import Point
from pdu.python.geometry_msgs.pdu_conv_Point import py_to_pdu_Point, pdu_to_py_Point

p = Point()
p.x = 1.23
p.y = 4.56
p.z = 7.89

pdu_bytes = py_to_pdu_Point(p)
restored = pdu_to_py_Point(pdu_bytes)
```

### JavaScript

Generated JS files live under `pdu/javascript/<pkg>/`.
Converters follow the `pdu_conv_<Msg>.js` naming convention.

## Service message generator (ROS .srv -> Hakoniwa .msg)

To convert a ROS `.srv` file into Hakoniwa `.msg` files:

```bash
python3 -m generators.generate_hako_service_msgs.main /path/to/YourService.srv \
  --out idl
```

Generated `.msg` files appear under `idl/<srv_pkg>_msgs/msg/`.

## Relationship to other components

- hakoniwa-core-pro: https://github.com/hakoniwalab/hakoniwa-core-pro
- hakoniwa-pdu-bridge-core: https://github.com/hakoniwalab/hakoniwa-pdu-bridge-core
- hakoniwa-pdu-endpoint: https://github.com/hakoniwalab/hakoniwa-pdu-endpoint
- hakoniwa-pdu-rpc: https://github.com/hakoniwalab/hakoniwa-pdu-rpc

## Status / Roadmap

Current status: Experimental, but internally used in Hakoniwa core components.

Planned improvements:

- PDU versioning and compatibility checks
- Validation and schema consistency tests
- CI integration for reproducible generation
- Additional language bindings

## Tradeoffs

This project deliberately makes the following tradeoffs:

- Larger repository size in exchange for deterministic layout preservation
- Diff noise in exchange for visible cross-language impact
- Strict Docker workflow in exchange for reproducible generation
- Reduced flexibility in exchange for binary contract stability

These tradeoffs are intentional and align with the requirements
of long-lived distributed robotics systems.

## FAQ

Why not generate on-the-fly?
Generated PDUs are treated as assets to ensure reproducible layouts, stable ABI,
and consistent artifacts across tools and CI.

Is this a ROS replacement?
No. This registry does not replace ROS build or deployment systems.
It only manages PDU definitions and generated artifacts.

How do I add messages?
Edit `config/ros_msgs.txt` and `config/search_path.txt`, then run the generator.

Why commit generated artifacts instead of ignoring them?
Committed outputs preserve binary layout stability, keep ABI compatibility across language
bindings, and enable reproducible CI while preventing toolchain drift.

What guarantees binary compatibility?
Offsets are calculated via compiled C layout, the generated size registry is committed,
and MetaData versioning is enforced.

## TODO

- (none)
