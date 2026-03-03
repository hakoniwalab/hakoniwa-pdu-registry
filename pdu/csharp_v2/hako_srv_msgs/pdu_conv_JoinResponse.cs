using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class JoinResponseConverter
    {
        public static JoinResponse PduToMsg(byte[] binaryData)
        {
            var obj = new JoinResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(JoinResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, JoinResponse obj, int baseOff)
        {
            obj.status_code = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.message = PduRuntime.ReadString(binaryData, baseOff + 4, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, JoinResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.status_code), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForString(obj.message, 128), parentOff + 4);
        }
    }
}
