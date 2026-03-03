# PDU Binary Format

This document provides the detailed binary layout for Hakoniwa PDUs.
It reflects the current implementation and notes planned extensions explicitly.

## Layout

```
[MetaData (24 bytes)][BaseData (C struct)][HeapData (variable)][ExtMeta planned]
```

- `MetaData` is fixed-size and always present.
- `BaseData` is a C struct with a fixed, language-agnostic layout.
- `HeapData` stores variable-length content referenced from `BaseData`.
- `ExtMeta` is planned and not implemented in this release.

## MetaData (24 bytes)

| Offset | Type     | Description                                                   |
| -----: | -------- | ------------------------------------------------------------- |
|      0 | uint32   | Magic number (`0x12345678`)                                   |
|      4 | uint32   | Version (currently `0x00000001`)                              |
|      8 | uint32   | BaseData offset (from MetaData start)                         |
|     12 | uint32   | HeapData offset (from MetaData start)                         |
|     16 | uint32   | Total size (MetaData + BaseData + HeapData [+ ExtMeta])       |
|     20 | uint8    | Epoch (generation tag, commit marker)                         |
|     21 | uint8    | Flags (bitfield; e.g., HAS_EXT_META when ExtMeta is appended) |
|     22 | uint8[2] | Reserved (must be 0)                                          |

### MetaData field semantics

- `magicno` must be `0x12345678`.
- `version` must be `0x00000001` in current implementations.
- `base_off` is `HAKO_PDU_META_DATA_SIZE()` in current creators.
- `heap_off` is `base_off + aligned(base_size)` with alignment `sizeof(void*)`.
- `total_size` is set by `hako_create_empty_pdu` to the allocated size.
  `hako_pdu_put_fixed_data` does not update this field.
- `epoch` is an 8-bit generation tag used for commit detection.
- `flags` are currently unused by runtime code and default to 0.
- `reserved` must be 0 and is initialized to 0 by creators.

## BaseData

- Stored as a C struct with fixed layout and padding preserved.
- Fixed-size fields live directly in BaseData.
- Variable-length fields are represented by an 8-byte reference:
  `int32 length` and `int32 offset (from HeapData start)`.

## HeapData

- Stores variable-length arrays, strings, and nested data.
- Packed without padding.
- Accessed via offsets stored in BaseData references.

## Variable-Length Array (`varray`) Rules

All `varray` fields use the same 8-byte reference in `BaseData` or in a heap-resident struct:

```text
int32 length
int32 offset_from_heap_start
```

Rules:

- `length` is the number of logical elements, not the byte size.
- `offset` is always relative to the start of `HeapData`.
- `length = 0` is valid.
- For `length = 0`, `offset` points to the current heap end at serialization time.
- Readers must treat `length = 0` as an empty array and must not read payload bytes.

### Memory Layout Image

#### Required reference cases: `length = 0 / 1 / 2`

Every `varray` implementation should be validated at least with these three cases:

```text
Case A: length = 0

BaseData / struct field
+----------------------+----------------------+
| length = 0           | offset = heap_end    |
+----------------------+----------------------+

HeapData
+---------------------------------------------+
| no payload for this varray                  |
+---------------------------------------------+
```

```text
Case B: length = 1

BaseData / struct field
+----------------------+----------------------+
| length = 1           | offset = X           |
+----------------------+----------------------+

HeapData
offset X
+----------------------+
| element[0] payload    |
+----------------------+
```

```text
Case C: length = 2

BaseData / struct field
+----------------------+----------------------+
| length = 2           | offset = X           |
+----------------------+----------------------+

HeapData
offset X
+----------------------+----------------------+
| element[0] payload    | element[1] payload    |
+----------------------+----------------------+
```

Why these three cases matter:

- `length = 0` verifies empty-array handling and offset stability
- `length = 1` verifies the simplest non-empty path
- `length = 2` is the first case that exposes broken interleaving in `struct varray` and nested `varray`

#### Primitive `varray`

Example: `float64[] data`

```text
BaseData
+----------------------+----------------------+
| data.length = 2      | data.offset = 0      |
+----------------------+----------------------+

HeapData
offset 0
+----------------------+----------------------+
| data[0] (8 bytes)    | data[1] (8 bytes)    |
+----------------------+----------------------+
```

#### `string[]` `varray`

Example: fixed-width string slot = 128 bytes

```text
BaseData
+----------------------+----------------------+
| name.length = 2      | name.offset = 0      |
+----------------------+----------------------+

HeapData
offset 0
+-------------------------------+-------------------------------+
| name[0] slot (128 bytes)      | name[1] slot (128 bytes)      |
| "a\\0" + unused bytes         | "b\\0" + unused bytes         |
+-------------------------------+-------------------------------+
```

#### Struct `varray`

Example: `SimpleVarray[] data`, element fixed size = 24 bytes

```text
BaseData
+----------------------+----------------------+
| data.length = 2      | data.offset = 0      |
+----------------------+----------------------+

HeapData
offset 0
+----------------------+----------------------+
| element[0] fixed 24B | element[1] fixed 24B |
+----------------------+----------------------+
```

The important rule is that all fixed-size element bodies are placed first.
If an element contains nested variable-length fields, those payloads come after this reserved area.

#### Nested `varray` inside struct `varray`

Example: `DisturbanceUserCustom[] d_user_custom`,
and each `DisturbanceUserCustom` contains `float64[] data`

```text
BaseData
+-------------------------------+-------------------------------+
| d_user_custom.length = 2      | d_user_custom.offset = 0      |
+-------------------------------+-------------------------------+

HeapData
offset 0
+-------------------------------+-------------------------------+
| elem[0] fixed part (8 bytes)  | elem[1] fixed part (8 bytes)  |
| inner len=2, off=16           | inner len=1, off=32           |
+-------------------------------+-------------------------------+
offset 16
+-------------------------------+-------------------------------+
| elem[0].data[0] (8 bytes)     | elem[0].data[1] (8 bytes)     |
+-------------------------------+-------------------------------+
offset 32
+-------------------------------+
| elem[1].data[0] (8 bytes)     |
+-------------------------------+
```

Incorrect interleaving such as:

```text
elem[0] fixed -> elem[0] nested payload -> elem[1] fixed
```

is not canonical and breaks interoperability once `length >= 2`.

### Primitive `varray`

- The payload is stored contiguously in `HeapData`.
- Element size is determined by the primitive type.
- `bool` uses the PDU primitive size, not a language-native boolean size.

### `string[]` `varray`

- The payload is stored as a contiguous fixed-width string array in `HeapData`.
- Each element occupies the message-defined fixed width.
- Each string is UTF-8 plus a trailing `\\0`, truncated if needed to fit the fixed-width slot.
- Unused bytes inside each fixed-width slot are not semantically significant.

### Struct `varray`

`C++` is the oracle for the canonical layout.

For a struct element type with fixed size `one_elm_size` and logical length `N`:

1. Reserve `N * one_elm_size` bytes in `HeapData` first.
2. Place each element's fixed-size struct body in that reserved region contiguously.
3. Place any nested variable-length payloads after the reserved fixed-size region.
4. Any nested `{length, offset}` references inside those elements are also relative to the start of `HeapData`.

This means a struct `varray` does not interleave:

- element 0 fixed part
- element 0 nested payload
- element 1 fixed part

Instead, the canonical layout is:

- all fixed parts for all elements
- then nested payloads

This rule is required for correct interoperation when:

- `N >= 2`
- the element struct itself contains one or more `varray` fields

### Nested `varray`

If a struct `varray` element contains another `varray`:

- the outer struct array still reserves all element fixed parts first
- the inner payloads are appended after that reserved region
- inner offsets are still heap-relative, not element-relative

## Epoch rules

Epoch is a generation tag, not a timestamp.
Only equality checks are valid.

Rules:

1. Compare only equality: `epoch_prev != epoch_curr`.
2. Do not use `<` or `>` comparisons.
3. 8-bit wrap-around is acceptable.

Commit rule:

1. Write BaseData and HeapData payloads.
2. Write ExtMeta only if implemented.
3. Update `epoch` last (commit marker).

Reader behavior:

1. If epoch changed, treat as a new generation.
2. If epoch unchanged, ignore.

## ExtMeta (planned)

ExtMeta is planned and not implemented in the current release.
This section documents intended behavior only.

Placement rules:

- Appended after HeapData.
- Never referenced from BaseData.
- Existing converters only resolve BaseData references into HeapData.

Write order:

1. Write BaseData and HeapData.
2. Append ExtMeta at the end of HeapData.
3. Set `MetaData.flags` with `HAS_EXT_META`.
4. Update `epoch` last.

Impact on existing converters:

- Current C#/Python converters only follow BaseData references.
- Appended ExtMeta is ignored by current implementations.
