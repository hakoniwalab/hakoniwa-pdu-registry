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
