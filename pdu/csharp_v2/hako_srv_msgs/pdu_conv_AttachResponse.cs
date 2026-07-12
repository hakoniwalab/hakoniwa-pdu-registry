using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class AttachResponseConverter
    {
        public static AttachResponse PduToMsg(byte[] binaryData)
        {
            var obj = new AttachResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AttachResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AttachResponse obj, int baseOff)
        {
            obj.result_code = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.session_id = PduRuntime.ReadUInt64(binaryData, baseOff + 8);
            obj.world_time = new LogicalTime();
            LogicalTimeConverter.BinaryReadRecursive(meta, binaryData, obj.world_time, baseOff + 16);
            obj.delta_asset_tick = PduRuntime.ReadUInt64(binaryData, baseOff + 32);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AttachResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.result_code), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.session_id), parentOff + 8);
            LogicalTimeConverter.BinaryWriteRecursive(parentOff + 16, writer, allocator, obj.world_time);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.delta_asset_tick), parentOff + 32);
        }
    }
}
