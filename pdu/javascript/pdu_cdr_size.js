// Auto-generated CDR minimum payload size registry
// Sizes include the 4-byte CDR encapsulation header.
// Variable-length sequences are counted as length 0; strings are counted as empty strings.
export const PDU_CDR_SIZE = {
  "hako_srv_msgs/AttachRequest": 20,
  "hako_srv_msgs/AttachRequestPacket": 44,
  "hako_srv_msgs/AttachResponse": 44,
  "hako_srv_msgs/AttachResponsePacket": 68,
  "hako_srv_msgs/DetachRequest": 12,
  "hako_srv_msgs/DetachRequestPacket": 36,
  "hako_srv_msgs/DetachResponse": 8,
  "hako_srv_msgs/DetachResponsePacket": 32,
  "hako_srv_msgs/GetWorldTimeRequest": 12,
  "hako_srv_msgs/GetWorldTimeRequestPacket": 36,
  "hako_srv_msgs/GetWorldTimeResponse": 28,
  "hako_srv_msgs/GetWorldTimeResponsePacket": 52,
  "hako_srv_msgs/LogicalTime": 20,
  "hako_srv_msgs/NotifyAssetTimeRequest": 28,
  "hako_srv_msgs/NotifyAssetTimeRequestPacket": 52,
  "hako_srv_msgs/NotifyAssetTimeResponse": 8,
  "hako_srv_msgs/NotifyAssetTimeResponsePacket": 32,
  "hako_srv_msgs/ServiceRequestHeader": 28,
  "hako_srv_msgs/ServiceResponseHeader": 28,
};

export function getSize(typeName) {
  return PDU_CDR_SIZE[typeName];
}
