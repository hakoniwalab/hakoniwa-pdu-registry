using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class RangeConverter
    {
        public static Range PduToMsg(byte[] binaryData)
        {
            var obj = new Range();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Range obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Range obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.radiation_type = PduRuntime.ReadUInt8(binaryData, baseOff + 136);
            obj.field_of_view = PduRuntime.ReadFloat32(binaryData, baseOff + 140);
            obj.min_range = PduRuntime.ReadFloat32(binaryData, baseOff + 144);
            obj.max_range = PduRuntime.ReadFloat32(binaryData, baseOff + 148);
            obj.range = PduRuntime.ReadFloat32(binaryData, baseOff + 152);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Range obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.radiation_type), parentOff + 136);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.field_of_view), parentOff + 140);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.min_range), parentOff + 144);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.max_range), parentOff + 148);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.range), parentOff + 152);
        }
    }
}
