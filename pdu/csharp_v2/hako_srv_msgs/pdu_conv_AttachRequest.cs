using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class AttachRequestConverter
    {
        public static AttachRequest PduToMsg(byte[] binaryData)
        {
            var obj = new AttachRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AttachRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AttachRequest obj, int baseOff)
        {
            obj.asset_name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.delta_asset_tick = PduRuntime.ReadUInt64(binaryData, baseOff + 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AttachRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.asset_name, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.delta_asset_tick), parentOff + 128);
        }
    }
}
