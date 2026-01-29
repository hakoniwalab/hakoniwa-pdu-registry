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
- Generated multi-language PDU artifacts (C / C++ / Python, etc.)
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

## Directory Structure

```

hakoniwa-pdu-registry
├── idl/                # Input definitions (ROS 2 msg, etc.)
├── template/          # Code generation templates
├── generators/         # Python-based generators
├── pdu/                # Generated PDU artifacts
│   └── types/
├── config/             # Message lists, search paths
├── docker/             # Reproducible build environment
└── docs/               # Design documents and specifications

````

---

## Quick Start

### 1. Clone the repository

```bash
git clone https://github.com/<your-org>/hakoniwa-pdu-registry.git
cd hakoniwa-pdu-registry
````

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

```bash
bash docker/run.bash
```

```bash
export PYTHONPATH=$PYTHONPATH:/path/to/hakoniwa-pdu-registry
python3 /path/to/hakoniwa-pdu-registry/utils/hakoniwa_pdu_generator/main.py /path/to/hakoniwa-pdu-registry/config/ros_msgs.txt
```

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

| Offset | Type   | Description               |
| -----: | ------ | ------------------------- |
|      0 | uint32 | Magic number (0x12345678) |
|      4 | uint32 | Version                   |
|      8 | uint32 | BaseData offset           |
|     12 | uint32 | HeapData offset           |
|     16 | uint32 | Total size                |

### BaseData

* Stored as a C struct
* Includes fixed-size fields and metadata for variable-length data
* Alignment and padding are preserved

### HeapData

* Stores variable-length arrays, strings, and nested data
* Packed without padding
* Accessed via offsets stored in BaseData

This design enables fast encoding/decoding and language-independent
binary compatibility.

---

## Relationship to Other Hakoniwa Components

* **hakoniwa-core-pro**: Runtime execution and simulation
* **hakoniwa-pdu-bridge**: Inter-process and inter-node communication
* **hakoniwa-pdu-endpoint**: PDU io interfaces

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
