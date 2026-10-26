// Auto-generated CDR minimum payload size registry
// Sizes include the 4-byte CDR encapsulation header.
// Variable-length sequences are counted as length 0; strings are counted as empty strings.
export const PDU_CDR_SIZE = {
  "builtin_interfaces/Time": 12,
  "geometry_msgs/Point": 28,
  "geometry_msgs/Pose": 60,
  "geometry_msgs/Quaternion": 36,
  "hako_msgs/ContactEvent": 69,
  "hako_msgs/ContactEventArray": 8,
  "hako_msgs/LightState": 21,
  "hako_msgs/LightStateArray": 24,
  "hako_srv_msgs/RenderCameraFrameRequest": 84,
  "hako_srv_msgs/RenderCameraFrameRequestPacket": 108,
  "hako_srv_msgs/RenderCameraFrameResponse": 140,
  "hako_srv_msgs/RenderCameraFrameResponsePacket": 164,
  "hako_srv_msgs/RenderCameraRequest": 76,
  "hako_srv_msgs/RenderCameraRequestPacket": 100,
  "hako_srv_msgs/RenderCameraResponse": 60,
  "hako_srv_msgs/RenderCameraResponsePacket": 84,
  "hako_srv_msgs/RenderObject": 76,
  "hako_srv_msgs/ServiceRequestHeader": 28,
  "hako_srv_msgs/ServiceResponseHeader": 28,
  "hako_srv_msgs/SetLightRequest": 44,
  "hako_srv_msgs/SetLightRequestPacket": 68,
  "hako_srv_msgs/SetLightResponse": 13,
  "hako_srv_msgs/SetLightResponsePacket": 37,
  "sensor_msgs/Image": 44,
  "std_msgs/Header": 17,
};

export function getSize(typeName) {
  return PDU_CDR_SIZE[typeName];
}
