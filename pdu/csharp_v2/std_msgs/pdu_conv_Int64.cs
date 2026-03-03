using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public static class Int64Converter
    {
        public static Int64 PduToMsg(byte[] binaryData)
        {
            var obj = new Int64();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Int64 obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Int64 obj, int baseOff)
        {
            obj.data = PduRuntime.ReadInt64(binaryData, baseOff + 0);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Int64 obj)
        {
            allocator.Add(PduRuntime.GetBinaryForInt64(obj.data), parentOff + 0);
        }
    }
}
