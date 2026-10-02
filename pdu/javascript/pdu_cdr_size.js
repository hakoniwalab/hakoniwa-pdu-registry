// Auto-generated CDR minimum payload size registry
// Sizes include the 4-byte CDR encapsulation header.
// Variable-length sequences are counted as length 0; strings are counted as empty strings.
export const PDU_CDR_SIZE = {
  "builtin_interfaces/Time": 12,
  "geometry_msgs/Point": 28,
  "hako_msgs/ContactEvent": 69,
  "hako_msgs/ContactEventArray": 8,
};

export function getSize(typeName) {
  return PDU_CDR_SIZE[typeName];
}
