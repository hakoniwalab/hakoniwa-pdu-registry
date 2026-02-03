# hakoniwa-pdu-registry

A central registry for Hakoniwa PDU definitions and their generated multi-language artifacts,  
ensuring consistent and reproducible PDU interfaces across runtimes and tools.

---

## Overview

`hakoniwa-pdu-registry` provides a central place to define, generate, and manage
Hakoniwa PDUs (Protocol Data Units).

PDUs are the first-class communication units in the Hakoniwa runtime.
This repository manages PDU definitions derived from ROS 2 IDL (`.msg` files),
their generated multi-language artifacts, and the templates and tools required
to reproduce them consistently.

Unlike simple code generators, this registry treats generated PDUs as
long-lived assets rather than disposable outputs.

---

## Motivation

ROS 2 IDL (`.msg`) files are easy to write, but they do not provide:

- A canonical representation of generated data layouts
- Long-term management of generated multi-language code
- Reproducible binary compatibility across runtimes and tools

In large-scale or long-lived distributed simulations, these limitations
become critical.

`hakoniwa-pdu-registry` addresses this gap by introducing a registry layer
where PDU definitions, templates, and generated artifacts are managed
as authoritative assets.

---

## Scope and Responsibilities

### This registry provides:

- PDU definitions derived from ROS 2 IDL
- Generated multi-language PDU artifacts (C / C++ / C# / Python / JavaScript)
- Template management for code generation
- Python-based generation tools
- Reproducible and language-agnostic PDU layouts

### This registry does NOT:

- Execute runtime communication
- Manage transport or middleware
- Replace ROS build or deployment systems

---

## Architecture Overview

```

ROS 2 IDL (.msg)
|
v
Python Generator
|
v
PDU Artifacts
|
v
Runtime / Bridge / Tools

```

The registry defines the full lifecycle of a PDU, from IDL definition
to runtime-consumable artifacts.

---

## Design Philosophy (Type Layers)

Hakoniwa uses a layered type model to maximize cross-language interoperability:

- **PDU (C-compatible type)**: `Hako_*` structs with a fixed, language-agnostic memory layout.
- **Hakoniwa C++ type**: `HakoCpp_*` structs using STL containers for ergonomics (ROS-free).
- **ROS 2 C++ type**: Standard ROS message types for ROS nodes.
- **Python type**: Pure-Python classes with type hints for Python users.

Conversions are done in stages (e.g., ROS 2 C++ → PDU; or custom C++ → Hakoniwa C++ → PDU),
so each component stays focused on its own responsibility.

---

## Directory Structure

```

hakoniwa-pdu-registry
├── idl/                # Input definitions (ROS 2 msg, etc.)
├── template/           # Code generation templates
├── generators/         # Python-based generators
├── pdu/                # Generated PDU artifacts
│   └── types/
│   └── offset/          # Offset files for BaseData layout
│   └── pdu_size/         # BaseData size files (aligned)
│   └── python/           # Python types and converters
│   └── javascript/       # JavaScript types and converters
├── config/             # Message lists, search paths
├── docker/             # Reproducible build environment
└── docs/               # Design documents and specifications

```

---

## Quick Start

### 1. Clone the repository

```bash
git clone https://github.com/<your-org>/hakoniwa-pdu-registry.git
cd hakoniwa-pdu-registry
```

### 2. Configure target messages

Edit the message list:

```text
config/ros_msgs.txt
```

Specify ROS 2 message types to be converted into PDUs:

```text
can_msgs/HakoCan
ev3_msgs/EV3PduSensor
ev3_msgs/EV3PduActuator
```

Edit search paths for ROS message definitions:

```text
config/search_path.txt
```

Example:

```text
/opt/ros/foxy/share
/workspace/src
```

### 3. Run the generator

Run the following commands inside the container started by `bash docker/run.bash`.

```bash
bash docker/run.bash
cd hakoniwa-pdu-registry
python3 -m generators.generate_hako_service_msgs.main <srv_file_path> --out idl
python3 -m generators.generate_hako_pdu_msgs.main config/ros_msgs.txt
```

`--out idl` writes generated `.msg` files under `idl/` so they are treated as registry inputs.



Generated PDU artifacts will appear under:

```text
pdu/types/
```

---

## PDU Binary Format (Summary)

Hakoniwa PDUs are serialized into the following binary layout:

```
[MetaData (24 bytes)][BaseData (C struct)][HeapData (variable)]
```

### MetaData (24 bytes)

| Offset | Type    | Description               |
| -----: | ------- | ------------------------- |
|      0 | uint32  | Magic number (0x12345678) |
|      4 | uint32  | Version                   |
|      8 | uint32  | BaseData offset           |
|     12 | uint32  | HeapData offset           |
|     16 | uint32  | Total size                |
|     20 | uint8   | Epoch (commit counter)    |
|     21 | uint8   | Flags                     |
|     22 | uint8[2] | Reserved                 |

### BaseData

* Stored as a C struct
* Includes fixed-size fields and metadata for variable-length data
* Alignment and padding are preserved
* Variable-length references use an 8-byte structure:
  - `int32 length`
  - `int32 offset (from HeapData start)`

### HeapData

* Stores variable-length arrays, strings, and nested data
* Packed without padding
* Accessed via offsets stored in BaseData

This design enables fast encoding/decoding and language-independent
binary compatibility.

---

## Epoch (Metadata)

Epoch is a generation tag per PDU. It is not a timestamp and must not be
compared by magnitude. Only "changed or not" matters.

Rules:

* Compare only equality: `epoch_prev != epoch_curr`
* Do not use `<` or `>` comparisons
* 8-bit wrap-around is acceptable

Why embed epoch in PDU MetaData:

* Allows immediate validation before reading payload
* Enables fast discard of stale data
* Minimal overhead (1 byte in MetaData)

### Commit rule

Writer order:

1. Write BaseData / HeapData payload
2. (Optional) write ExtMeta
3. Update epoch last (commit)

Reader behavior:

* If epoch changed, treat as a new generation
* If epoch unchanged, ignore

Note: Epoch is primarily used by Runtime Delegation (RD) for ownership
generation tracking. RD is mentioned here as background only; its formal
specification is out of scope for this README.

---

## PDU Generation Workflow

1. Resolve dependencies from the input ROS message list.
2. Generate multi-language type definitions (C/C++/C#/Python/JavaScript).
3. Calculate BaseData offsets by compiling a small C program.
4. Generate Python and JavaScript converters from offset files.

Generated offset files are placed under `pdu/offset/`, and aligned size
files are placed under `pdu/pdu_size/`. For Unity and other tools that
disallow the `.offset` extension, the same content is also emitted under
`pdu/offset_text/` with `.txt` filenames.

---

## Python Support

Generated Python files include:

- `pdu/python/pdu_utils.py`: shared PDU metadata and helpers
- `pdu/python/binary_io.py`: canonical MetaData definitions and low-level binary IO
- `pdu/python/<pkg>/pdu_pytype_<msg>.py`: Python data classes
- `pdu/python/<pkg>/pdu_conv_<msg>.py`: PDU byte conversion helpers

### Example (Python)

```python
import sys
sys.path.append('/path/to/hakoniwa-pdu-registry')

from pdu.python.geometry_msgs.pdu_pytype_Point import Point
from pdu.python.geometry_msgs.pdu_conv_Point import py_to_pdu_Point, pdu_to_py_Point

p = Point()
p.x = 1.23
p.y = 4.56
p.z = 7.89

pdu_bytes = py_to_pdu_Point(p)
restored = pdu_to_py_Point(pdu_bytes)
```

---

## Service Message Generator (ROS .srv → Hakoniwa .msg)

This tool generates request/response and packet `.msg` files from a ROS `.srv`.

```bash
python3 -m generators.generate_hako_service_msgs.main <srv_file_path> --out <output_base_directory>
```

Output structure:

```
<output_base_directory>/
└── <srv_pkg>_msgs/
    └── msg/
        ├── <ServiceName>Request.msg
        ├── <ServiceName>Response.msg
        ├── <ServiceName>RequestPacket.msg
        └── <ServiceName>ResponsePacket.msg
```

Notes:
- Constants in `.srv` are ignored.
- Empty request/response (after constants) is an error.
- `ServiceRequestHeader.msg` and `ServiceResponseHeader.msg` are provided by Hakoniwa and not generated.

---

## Relationship to Other Hakoniwa Components

* **[hakoniwa-core-pro](https://github.com/hakoniwalab/hakoniwa-core-pro)**: Runtime execution and simulation
* **[hakoniwa-pdu-bridge-core](https://github.com/hakoniwalab/hakoniwa-pdu-bridge-core)**: Inter-process and inter-node communication
* **[hakoniwa-pdu-endpoint](https://github.com/hakoniwalab/hakoniwa-pdu-endpoint)**: PDU io interfaces
* **[hakoniwa-pdu-rpc](https://github.com/hakoniwalab/hakoniwa-pdu-rpc)**: Remote procedure call over PDUs

`hakoniwa-pdu-registry` provides the authoritative PDU definitions
used by these components.

---

## Status and Roadmap

Current status: **Experimental**

Planned improvements:

* PDU versioning and compatibility checks
* Validation and schema consistency tests
* CI integration for reproducible generation
* Additional language bindings

---

## Extended MetaData (ExtMeta) Placement

Note: ExtMeta support is planned for the future. This section documents the
intended specification only, and no implementation is included in this release.

### Placement rules

* Appended at the end of HeapData
* Never referenced from BaseData
* Existing converters only resolve (offset, size) references in BaseData, so
  the extended region is completely ignored

```
[MetaData][BaseData][HeapData][ExtMeta][(optional Footer)]
```

### Write order (important)

1. Write BaseData / HeapData body
2. Write ExtMeta at the end of HeapData
3. (Optional) write Footer
4. Set MetaData.flags with HAS_EXT_META
5. Update epoch last (commit)

---

## Impact on Existing Converters (C#/Python)

* Existing converters:
  * Only follow (offset, size) references from BaseData into HeapData
  * Do not interpret the entire HeapData semantically
* Therefore:
  * Appending to the Heap tail is ignored and has no effect
  * Even with Version=2, behavior is identical to v1 unless ExtMeta is read

Only new implementations (Bridge / Conductor) are affected.

---

## Intended Uses of ExtMeta

* Hakoniwa core logical time
* RD helper flags
* Debug/observation information

Notes:
* Large data (e.g., images) should continue to use BaseData/HeapData references
* ExtMeta is limited to lightweight, auxiliary information
