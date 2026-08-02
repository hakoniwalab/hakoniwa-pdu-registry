using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sample_action_msgs;
using Hakoniwa.Pdu.CSharpV2.hako_action_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sample_action_msgs
{
    public static class FibonacciActionResponseConverter
    {
        public static FibonacciActionResponse PduToMsg(byte[] binaryData)
        {
            var obj = new FibonacciActionResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(FibonacciActionResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, FibonacciActionResponse obj, int baseOff)
        {
            obj.header = new ActionResponseHeader();
            ActionResponseHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.body = new FibonacciResult();
            FibonacciResultConverter.BinaryReadRecursive(meta, binaryData, obj.body, baseOff + 20);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, FibonacciActionResponse obj)
        {
            ActionResponseHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            FibonacciResultConverter.BinaryWriteRecursive(parentOff + 20, writer, allocator, obj.body);
        }
    }
}
