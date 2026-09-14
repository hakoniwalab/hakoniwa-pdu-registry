using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public static class EmptyConverter
    {
        public static Empty PduToMsg(byte[] binaryData)
        {
            var obj = new Empty();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Empty obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Empty obj, int baseOff)
        {
            obj.hako_dummy = PduRuntime.ReadUInt8(binaryData, baseOff + 0);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Empty obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.hako_dummy), parentOff + 0);
        }
    }
}
