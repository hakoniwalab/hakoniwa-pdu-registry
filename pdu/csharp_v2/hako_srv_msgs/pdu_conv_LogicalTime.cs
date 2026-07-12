using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class LogicalTimeConverter
    {
        public static LogicalTime PduToMsg(byte[] binaryData)
        {
            var obj = new LogicalTime();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(LogicalTime obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, LogicalTime obj, int baseOff)
        {
            obj.generation = PduRuntime.ReadUInt64(binaryData, baseOff + 0);
            obj.offset_tick = PduRuntime.ReadUInt64(binaryData, baseOff + 8);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, LogicalTime obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.generation), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.offset_tick), parentOff + 8);
        }
    }
}
