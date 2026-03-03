using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class AddTwoIntsResponseConverter
    {
        public static AddTwoIntsResponse PduToMsg(byte[] binaryData)
        {
            var obj = new AddTwoIntsResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AddTwoIntsResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AddTwoIntsResponse obj, int baseOff)
        {
            obj.sum = PduRuntime.ReadInt64(binaryData, baseOff + 0);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AddTwoIntsResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForInt64(obj.sum), parentOff + 0);
        }
    }
}
