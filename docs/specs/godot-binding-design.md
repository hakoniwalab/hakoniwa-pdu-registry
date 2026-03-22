# Godot Binding Design

This document defines the design for Godot support in `hakoniwa-pdu-registry`.

The goal is to provide:

- binary PDU conversion executed in `C++`
- a Godot-friendly data contract for `GDScript`
- generated typed GDScript classes for message access
- deterministic behavior aligned with the existing PDU offset contract

## Design Goal

Godot support must preserve the same binary contract as the existing language targets.

The design must avoid:

- reinterpreting binary layout in `GDScript`
- depending on `std::vector` / `std::string` as the public Godot API
- duplicating layout logic in both `C++` and `GDScript`

The design should instead:

1. decode and encode PDU bytes in `C++`
2. expose a stable Godot-facing intermediate representation
3. generate typed `GDScript` classes from the same message definitions

## Chosen Architecture

Godot support uses a two-layer design.

### Layer 1: `C++` binary converter

The generated `C++` converter handles:

- `PackedByteArray -> Dictionary/Array/Packed*Array`
- `Dictionary/Array/Packed*Array -> PackedByteArray`

This layer is responsible for:

- metadata validation
- offset-based field access
- heap-relative `varray` decoding and encoding
- canonical nested `struct varray` layout

This layer is the only layer that touches raw PDU bytes.

### Layer 2: generated `GDScript` typed classes

Generated `GDScript` classes provide:

- typed members
- `from_dict()` for constructing typed objects from the Godot-facing intermediate representation
- `to_dict()` for converting typed objects back into the same intermediate representation

This layer is responsible for usability in game logic, editor scripts, and scene-side code.

## Why `Dictionary` / `Array` is Used as the Intermediate Contract

The public Godot API should not expose the existing `HakoCpp_*` types directly.

Reasons:

- it would require an extra conversion step from STL types into Godot types
- it would make Godot bindings depend on a C++-specific intermediate model
- it would increase copying for nested structures and arrays
- it would couple Godot support to the current C++ message-type representation

Instead, the Godot-facing contract is:

- simple
- dynamic
- easy to inspect and test
- natural for both `C++` GDExtension code and `GDScript`

This intermediate contract is not a fallback for missing Godot support.
It is an intentional separation between:

- wire/binary conversion
- script-friendly typed object construction

## Why Not Convert Directly to Typed GDScript Objects in `C++`

Direct construction of user-defined typed script objects from `C++` is possible only with a heavier object-registration design.

That approach would require:

- message-specific Godot classes registered from `C++`
- more complex object lifecycle handling
- tighter coupling between generated native classes and script API design

That may become a future optimization path, but it is not the initial target.

The initial design optimizes for:

- deterministic binary correctness
- implementation simplicity
- generated type safety at the `GDScript` layer
- testability

## Godot Data Contract

The intermediate representation uses only Godot-native values:

- `bool`
- `int`
- `float`
- `String`
- `Dictionary`
- `Array`
- `PackedByteArray`
- `PackedInt32Array`
- `PackedInt64Array`
- `PackedFloat32Array`
- `PackedFloat64Array`

Selection rules:

- primitive scalar -> matching Godot scalar type
- string -> `String`
- nested struct -> `Dictionary`
- fixed primitive array -> packed array when possible, otherwise `Array`
- variable primitive array -> packed array when possible, otherwise `Array`
- fixed struct array -> `Array[Dictionary-like payload]`
- variable struct array -> `Array[Dictionary-like payload]`
- fixed string array -> `Array[String]`
- variable string array -> `Array[String]`

## Typed `GDScript` Class Contract

Each generated message class should:

- extend `RefCounted`
- declare one member per ROS field
- initialize each member with a stable default
- provide `static func from_dict(d: Dictionary)`
- provide `func to_dict() -> Dictionary`

Example shape:

```gdscript
class_name JointState
extends RefCounted

var header: Header = Header.new()
var name: Array[String] = []
var position: PackedFloat64Array = PackedFloat64Array()
var velocity: PackedFloat64Array = PackedFloat64Array()
var effort: PackedFloat64Array = PackedFloat64Array()
```

## Type Mapping Policy

The following mapping is the initial policy.

| ROS/PDU type | Godot intermediate | Generated `GDScript` member |
| --- | --- | --- |
| `bool` | `bool` | `bool` |
| `int8` / `uint8` / `int16` / `uint16` / `int32` / `uint32` | `int` | `int` |
| `int64` | `int` | `int` |
| `uint64` | `int` by default | `int` |
| `float32` / `float64` | `float` | `float` |
| `string` | `String` | `String` |
| `uint8[]` payload-like field | `PackedByteArray` | `PackedByteArray` |
| numeric primitive arrays | packed array when available | packed array when available |
| `string[]` | `Array[String]` | `Array[String]` |
| struct | `Dictionary` | generated `RefCounted` type |
| struct array | `Array` of `Dictionary` | `Array` of generated type |

Notes:

- `uint64` may need a fallback policy if strict unsigned range preservation becomes necessary.
- the initial version assumes values fit within Godot `int` usage constraints in target deployments
- if exact unsigned 64-bit preservation becomes mandatory, the contract can be extended to encode those values as `String`

## Generation Targets

The Godot design adds new generated outputs.

### Generated native side

- `pdu/godot_cpp_runtime/`
  shared Godot runtime helpers for metadata, binary IO, and packed-array helpers
- `pdu/godot_cpp/<pkg>/`
  generated per-message converters for `PackedByteArray <-> Dictionary`

### Generated script side

- `pdu/godot_gd/<pkg>/`
  generated typed `GDScript` message classes

## Responsibilities

### `C++` Godot runtime/converter

- parse and validate PDU metadata
- read and write scalar fields by offset
- read and write fixed arrays
- read and write `varray`
- preserve canonical `struct varray` layout
- recursively build `Dictionary` / `Array` payloads

### generated `GDScript` classes

- define a stable high-level API
- turn `Dictionary` payloads into typed objects
- turn typed objects back into `Dictionary`

## Testing Strategy

Testing should be split by layer.

### Native converter tests

The native layer should be validated against the existing `C++` oracle expectations:

- scalar fields
- fixed arrays
- fixed strings
- primitive `varray`
- string `varray`
- struct `varray`
- nested `varray`
- `size=0 / 1 / 2` cases

### Script conversion tests

The script layer should validate:

- `from_dict()` correctness
- `to_dict()` correctness
- nested struct conversion
- packed array preservation

## Non-Goals for the Initial Version

The first version does not attempt:

- direct `C++ -> registered message object` construction
- editor plugin integration
- automatic Godot scene/resource serialization features
- compatibility shims for multiple Godot major versions

## Implementation Plan

1. add Godot-specific templates and generator entrypoints
2. generate typed `GDScript` classes
3. generate `C++` Godot runtime helpers
4. generate per-message `PackedByteArray <-> Dictionary` converters
5. add test fixtures for representative messages
6. validate `varray size=0/1/2` and nested layout behavior

## Summary

The chosen Godot design is:

- binary conversion in generated `C++`
- a stable Godot-native intermediate contract using `Dictionary` / `Array` / packed arrays
- generated typed `GDScript` classes on top of that contract

This keeps binary semantics deterministic while giving Godot users an ergonomic typed API.
