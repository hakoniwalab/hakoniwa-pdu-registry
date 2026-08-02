# Auto-generated CDR minimum payload size registry
# Sizes include the 4-byte CDR encapsulation header.
# Variable-length sequences are counted as length 0; strings are counted as empty strings.
PDU_CDR_SIZE = {
    "hako_action_msgs/ActionFeedbackHeader": 28,
    "hako_action_msgs/ActionRequestHeader": 24,
    "hako_action_msgs/ActionResponseHeader": 24,
}

def get_size(type_name: str):
    return PDU_CDR_SIZE.get(type_name)
