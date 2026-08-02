using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sample_action_msgs;
using Hakoniwa.Pdu.CSharpV2.hako_action_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sample_action_msgs
{
    public static class FibonacciActionRequestConverter
    {
        public static FibonacciActionRequest PduToMsg(byte[] binaryData)
        {
            var obj = new FibonacciActionRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(FibonacciActionRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, FibonacciActionRequest obj, int baseOff)
        {
            obj.header = new ActionRequestHeader();
            ActionRequestHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.body = new FibonacciGoal();
            FibonacciGoalConverter.BinaryReadRecursive(meta, binaryData, obj.body, baseOff + 20);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, FibonacciActionRequest obj)
        {
            ActionRequestHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            FibonacciGoalConverter.BinaryWriteRecursive(parentOff + 20, writer, allocator, obj.body);
        }
    }
}
