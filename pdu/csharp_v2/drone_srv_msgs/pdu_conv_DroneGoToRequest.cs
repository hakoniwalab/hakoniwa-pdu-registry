using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.drone_srv_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public static class DroneGoToRequestConverter
    {
        public static DroneGoToRequest PduToMsg(byte[] binaryData)
        {
            var obj = new DroneGoToRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(DroneGoToRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, DroneGoToRequest obj, int baseOff)
        {
            obj.drone_name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.target_pose = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.target_pose, baseOff + 128);
            obj.speed_m_s = PduRuntime.ReadFloat32(binaryData, baseOff + 152);
            obj.yaw_deg = PduRuntime.ReadFloat32(binaryData, baseOff + 156);
            obj.tolerance_m = PduRuntime.ReadFloat32(binaryData, baseOff + 160);
            obj.timeout_sec = PduRuntime.ReadFloat32(binaryData, baseOff + 164);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, DroneGoToRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.drone_name, 128), parentOff + 0);
            Vector3Converter.BinaryWriteRecursive(parentOff + 128, writer, allocator, obj.target_pose);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.speed_m_s), parentOff + 152);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.yaw_deg), parentOff + 156);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.tolerance_m), parentOff + 160);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.timeout_sec), parentOff + 164);
        }
    }
}
