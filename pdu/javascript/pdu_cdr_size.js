// Auto-generated CDR minimum payload size registry
// Sizes include the 4-byte CDR encapsulation header.
// Variable-length sequences are counted as length 0; strings are counted as empty strings.
export const PDU_CDR_SIZE = {
  "hako_action_msgs/ActionFeedbackHeader": 28,
  "hako_action_msgs/ActionRequestHeader": 24,
  "hako_action_msgs/ActionResponseHeader": 24,
};

export function getSize(typeName) {
  return PDU_CDR_SIZE[typeName];
}
