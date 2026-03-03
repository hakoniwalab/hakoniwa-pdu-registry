using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class ShareObjectOwnerRequestConverter
    {
        public static ShareObjectOwnerRequest PduToMsg(byte[] binaryData)
        {
            var obj = new ShareObjectOwnerRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ShareObjectOwnerRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ShareObjectOwnerRequest obj, int baseOff)
        {
            obj.object_name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.request_type = PduRuntime.ReadUInt32(binaryData, baseOff + 128);
            obj.new_owner_id = PduRuntime.ReadUInt32(binaryData, baseOff + 132);
            obj.request_time = PduRuntime.ReadUInt64(binaryData, baseOff + 136);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ShareObjectOwnerRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.object_name, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.request_type), parentOff + 128);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.new_owner_id), parentOff + 132);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.request_time), parentOff + 136);
        }
    }
}
