using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class ShareObjectOwnerConverter
    {
        public static ShareObjectOwner PduToMsg(byte[] binaryData)
        {
            var obj = new ShareObjectOwner();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ShareObjectOwner obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ShareObjectOwner obj, int baseOff)
        {
            obj.object_name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.owner_id = PduRuntime.ReadUInt32(binaryData, baseOff + 128);
            obj.last_update = PduRuntime.ReadUInt64(binaryData, baseOff + 136);
            obj.pos = new Twist();
            TwistConverter.BinaryReadRecursive(meta, binaryData, obj.pos, baseOff + 144);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ShareObjectOwner obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.object_name, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.owner_id), parentOff + 128);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.last_update), parentOff + 136);
            TwistConverter.BinaryWriteRecursive(parentOff + 144, writer, allocator, obj.pos);
        }
    }
}
