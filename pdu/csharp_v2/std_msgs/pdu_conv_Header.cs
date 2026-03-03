using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.std_msgs;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public static class HeaderConverter
    {
        public static Header PduToMsg(byte[] binaryData)
        {
            var obj = new Header();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Header obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Header obj, int baseOff)
        {
            obj.stamp = new Time();
            TimeConverter.BinaryReadRecursive(meta, binaryData, obj.stamp, baseOff + 0);
            obj.frame_id = PduRuntime.ReadString(binaryData, baseOff + 8, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Header obj)
        {
            TimeConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.stamp);
            allocator.Add(PduRuntime.GetBinaryForString(obj.frame_id, 128), parentOff + 8);
        }
    }
}
