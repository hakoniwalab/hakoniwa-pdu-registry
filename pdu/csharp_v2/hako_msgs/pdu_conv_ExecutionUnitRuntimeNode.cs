using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class ExecutionUnitRuntimeNodeConverter
    {
        public static ExecutionUnitRuntimeNode PduToMsg(byte[] binaryData)
        {
            var obj = new ExecutionUnitRuntimeNode();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ExecutionUnitRuntimeNode obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ExecutionUnitRuntimeNode obj, int baseOff)
        {
            obj.node_id = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ExecutionUnitRuntimeNode obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.node_id), parentOff + 0);
        }
    }
}
