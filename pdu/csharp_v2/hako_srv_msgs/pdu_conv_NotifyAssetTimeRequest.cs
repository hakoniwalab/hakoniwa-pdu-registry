using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class NotifyAssetTimeRequestConverter
    {
        public static NotifyAssetTimeRequest PduToMsg(byte[] binaryData)
        {
            var obj = new NotifyAssetTimeRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(NotifyAssetTimeRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, NotifyAssetTimeRequest obj, int baseOff)
        {
            obj.session_id = PduRuntime.ReadUInt64(binaryData, baseOff + 0);
            obj.asset_time = new LogicalTime();
            LogicalTimeConverter.BinaryReadRecursive(meta, binaryData, obj.asset_time, baseOff + 8);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, NotifyAssetTimeRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.session_id), parentOff + 0);
            LogicalTimeConverter.BinaryWriteRecursive(parentOff + 8, writer, allocator, obj.asset_time);
        }
    }
}
