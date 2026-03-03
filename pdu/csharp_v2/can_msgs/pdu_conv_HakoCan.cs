using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.can_msgs;

namespace Hakoniwa.Pdu.CSharpV2.can_msgs
{
    public static class HakoCanConverter
    {
        public static HakoCan PduToMsg(byte[] binaryData)
        {
            var obj = new HakoCan();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoCan obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoCan obj, int baseOff)
        {
            obj.head = new HakoCanHead();
            HakoCanHeadConverter.BinaryReadRecursive(meta, binaryData, obj.head, baseOff + 0);
            obj.body = new HakoCanBody();
            HakoCanBodyConverter.BinaryReadRecursive(meta, binaryData, obj.body, baseOff + 20);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoCan obj)
        {
            HakoCanHeadConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.head);
            HakoCanBodyConverter.BinaryWriteRecursive(parentOff + 20, writer, allocator, obj.body);
        }
    }
}
