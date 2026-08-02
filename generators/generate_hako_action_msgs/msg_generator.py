PRIMITIVES = {
    "bool", "int8", "uint8", "int16", "uint16", "int32", "uint32",
    "int64", "uint64", "float32", "float64", "string", "char", "byte",
    "time", "duration",
}


class MsgGenerator:
    def __init__(self, context):
        self.context = context

    def generate_data_msg(self, fields):
        lines = []
        for field in fields:
            package = field.get("package") or self.context.msg_package_name
            typename = self._qualify(field["type"], package)
            if field.get("is_array"):
                size = field.get("array_size")
                typename += f"[{size}]" if size is not None else "[]"
            lines.append(f"{typename} {field['name']}")
        return "\n".join(lines)

    def generate_request_msg(self):
        return self._packet("ActionRequestHeader", self.context.action_name + "Goal")

    def generate_response_msg(self):
        return self._packet("ActionResponseHeader", self.context.action_name + "Result")

    def generate_feedback_msg(self):
        return self._packet("ActionFeedbackHeader", self.context.action_name + "Feedback")

    def _packet(self, header_type, body_type):
        return "\n".join([
            f"{self.context.header_package_name}/{header_type} header",
            f"{body_type} body",
        ])

    def _qualify(self, typename, package):
        if "/" in typename or typename in PRIMITIVES:
            return typename
        if package == self.context.msg_package_name:
            return typename
        return f"{package}/{typename}" if package else typename
