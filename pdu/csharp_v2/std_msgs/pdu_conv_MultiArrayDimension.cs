using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public static class MultiArrayDimensionConverter
    {
        public static MultiArrayDimension PduToMsg(byte[] binaryData)
        {
            var obj = new MultiArrayDimension();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(MultiArrayDimension obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, MultiArrayDimension obj, int baseOff)
        {
            obj.label = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.size = PduRuntime.ReadUInt32(binaryData, baseOff + 128);
            obj.stride = PduRuntime.ReadUInt32(binaryData, baseOff + 132);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, MultiArrayDimension obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.label, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.size), parentOff + 128);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.stride), parentOff + 132);
        }
    }
}
