using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class GetWorldTimeResponseConverter
    {
        public static GetWorldTimeResponse PduToMsg(byte[] binaryData)
        {
            var obj = new GetWorldTimeResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(GetWorldTimeResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, GetWorldTimeResponse obj, int baseOff)
        {
            obj.result_code = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.world_time = new LogicalTime();
            LogicalTimeConverter.BinaryReadRecursive(meta, binaryData, obj.world_time, baseOff + 8);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, GetWorldTimeResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.result_code), parentOff + 0);
            LogicalTimeConverter.BinaryWriteRecursive(parentOff + 8, writer, allocator, obj.world_time);
        }
    }
}
