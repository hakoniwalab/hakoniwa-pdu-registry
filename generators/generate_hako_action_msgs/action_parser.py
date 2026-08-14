from generators.generate_hako_pdu_msgs.primitive_types import (
    is_constant_definition,
    reject_unsupported_builtin_type,
)


class ActionParser:
    def __init__(self, context):
        self.context = context

    def parse(self):
        sections = [[]]
        with open(self.context.action_file_path, "r", encoding="utf-8") as action_file:
            for raw_line in action_file:
                line = raw_line.split("#", 1)[0].strip()
                if not line:
                    continue
                if line == "---":
                    sections.append([])
                    continue
                if is_constant_definition(line):
                    # Hakoniwa PDU IDL does not support ROS constants.
                    continue
                sections[-1].append(self._parse_field(line))

        if len(sections) != 3:
            raise ValueError(
                "Invalid .action definition: expected exactly two '---' separators "
                "for Goal, Result, and Feedback sections."
            )
        return tuple(sections)

    def _parse_field(self, line):
        tokens = line.split()
        if len(tokens) != 2:
            raise ValueError(f"Invalid field line: '{line}'")

        field_type, field_name = tokens
        reject_unsupported_builtin_type(field_type)
        is_array = False
        array_size = None
        if field_type.endswith("]") and "[" in field_type:
            base_type, array_spec = field_type.rsplit("[", 1)
            array_spec = array_spec[:-1]
            is_array = True
            if array_spec:
                if array_spec.startswith("<="):
                    raise ValueError(
                        f"Bounded arrays are not supported by the current PDU generator: '{line}'"
                    )
                array_size = int(array_spec)
            field_type = base_type

        package = None
        if "/" in field_type:
            package, field_type = field_type.split("/", 1)

        return {
            "type": field_type,
            "name": field_name,
            "package": package,
            "is_array": is_array,
            "array_size": array_size,
        }
