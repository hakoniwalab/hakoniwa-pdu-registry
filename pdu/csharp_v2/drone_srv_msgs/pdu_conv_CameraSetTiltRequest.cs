using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.drone_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public static class CameraSetTiltRequestConverter
    {
        public static CameraSetTiltRequest PduToMsg(byte[] binaryData)
        {
            var obj = new CameraSetTiltRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(CameraSetTiltRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, CameraSetTiltRequest obj, int baseOff)
        {
            obj.drone_name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.tilt_angle_deg = PduRuntime.ReadFloat32(binaryData, baseOff + 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, CameraSetTiltRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.drone_name, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.tilt_angle_deg), parentOff + 128);
        }
    }
}
