using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class AddTwoIntsRequestConverter
    {
        public static AddTwoIntsRequest PduToMsg(byte[] binaryData)
        {
            var obj = new AddTwoIntsRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AddTwoIntsRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AddTwoIntsRequest obj, int baseOff)
        {
            obj.a = PduRuntime.ReadInt64(binaryData, baseOff + 0);
            obj.b = PduRuntime.ReadInt64(binaryData, baseOff + 8);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AddTwoIntsRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForInt64(obj.a), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForInt64(obj.b), parentOff + 8);
        }
    }
}
