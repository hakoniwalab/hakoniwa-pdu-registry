using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public static class HakoAHRS2Converter
    {
        public static HakoAHRS2 PduToMsg(byte[] binaryData)
        {
            var obj = new HakoAHRS2();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoAHRS2 obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoAHRS2 obj, int baseOff)
        {
            obj.roll = PduRuntime.ReadFloat32(binaryData, baseOff + 0);
            obj.pitch = PduRuntime.ReadFloat32(binaryData, baseOff + 4);
            obj.yaw = PduRuntime.ReadFloat32(binaryData, baseOff + 8);
            obj.altitude = PduRuntime.ReadFloat32(binaryData, baseOff + 12);
            obj.lat = PduRuntime.ReadInt32(binaryData, baseOff + 16);
            obj.lng = PduRuntime.ReadInt32(binaryData, baseOff + 20);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoAHRS2 obj)
        {
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.roll), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.pitch), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.yaw), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.altitude), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.lat), parentOff + 16);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.lng), parentOff + 20);
        }
    }
}
