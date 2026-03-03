using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class PointFieldConverter
    {
        public static PointField PduToMsg(byte[] binaryData)
        {
            var obj = new PointField();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(PointField obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, PointField obj, int baseOff)
        {
            obj.name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.offset = PduRuntime.ReadUInt32(binaryData, baseOff + 128);
            obj.datatype = PduRuntime.ReadUInt8(binaryData, baseOff + 132);
            obj.count = PduRuntime.ReadUInt32(binaryData, baseOff + 136);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, PointField obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.name, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.offset), parentOff + 128);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.datatype), parentOff + 132);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.count), parentOff + 136);
        }
    }
}
