"""ROS built-in type policy shared by the Hakoniwa PDU generators."""

import re

ROS_BUILTIN_TYPES = (
    "bool",
    "byte",
    "char",
    "float32",
    "float64",
    "int8",
    "uint8",
    "int16",
    "uint16",
    "int32",
    "uint32",
    "int64",
    "uint64",
    "string",
    "wstring",
)

SUPPORTED_BUILTIN_TYPES = tuple(
    type_name for type_name in ROS_BUILTIN_TYPES if type_name != "wstring"
)

SUPPORTED_PRIMITIVE_TYPES = tuple(
    type_name
    for type_name in SUPPORTED_BUILTIN_TYPES
    if type_name != "string"
)

CANONICAL_PRIMITIVE_TYPES = {
    "byte": "uint8",
    "char": "uint8",
}


def canonical_primitive_type(type_name: str) -> str:
    """Return the Hakoniwa canonical primitive name for a ROS type name."""
    return CANONICAL_PRIMITIVE_TYPES.get(type_name, type_name)


def ros_base_type(type_name: str) -> str:
    """Strip ROS array and bounded-string suffixes from a field type."""
    base_type = type_name.split("[", 1)[0].strip()
    return base_type.split("<=", 1)[0].strip()


def reject_unsupported_builtin_type(type_name: str) -> None:
    """Reject built-ins for which Hakoniwa has no defined wire representation."""
    if "/" not in type_name and ros_base_type(type_name) == "wstring":
        raise ValueError(
            "Unsupported ROS built-in type 'wstring' in field type "
            f"'{type_name}': Hakoniwa PDU does not define a wstring wire representation"
        )


def is_constant_definition(line: str) -> bool:
    """Return true for ROS constant assignment, excluding bounded-type ``<=``."""
    return re.search(r"(?<!<)=", line) is not None
