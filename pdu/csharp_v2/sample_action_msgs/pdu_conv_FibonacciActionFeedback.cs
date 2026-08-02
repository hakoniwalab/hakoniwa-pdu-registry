using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sample_action_msgs;
using Hakoniwa.Pdu.CSharpV2.hako_action_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sample_action_msgs
{
    public static class FibonacciActionFeedbackConverter
    {
        public static FibonacciActionFeedback PduToMsg(byte[] binaryData)
        {
            var obj = new FibonacciActionFeedback();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(FibonacciActionFeedback obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, FibonacciActionFeedback obj, int baseOff)
        {
            obj.header = new ActionFeedbackHeader();
            ActionFeedbackHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.body = new FibonacciFeedback();
            FibonacciFeedbackConverter.BinaryReadRecursive(meta, binaryData, obj.body, baseOff + 24);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, FibonacciActionFeedback obj)
        {
            ActionFeedbackHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            FibonacciFeedbackConverter.BinaryWriteRecursive(parentOff + 24, writer, allocator, obj.body);
        }
    }
}
