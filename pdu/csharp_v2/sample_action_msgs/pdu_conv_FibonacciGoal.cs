using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sample_action_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sample_action_msgs
{
    public static class FibonacciGoalConverter
    {
        public static FibonacciGoal PduToMsg(byte[] binaryData)
        {
            var obj = new FibonacciGoal();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(FibonacciGoal obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, FibonacciGoal obj, int baseOff)
        {
            obj.order = PduRuntime.ReadInt32(binaryData, baseOff + 0);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, FibonacciGoal obj)
        {
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.order), parentOff + 0);
        }
    }
}
