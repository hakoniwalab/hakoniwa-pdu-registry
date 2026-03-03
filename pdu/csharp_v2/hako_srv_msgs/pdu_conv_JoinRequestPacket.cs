using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class JoinRequestPacketConverter
    {
        public static JoinRequestPacket PduToMsg(byte[] binaryData)
        {
            var obj = new JoinRequestPacket();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(JoinRequestPacket obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, JoinRequestPacket obj, int baseOff)
        {
            obj.header = new ServiceRequestHeader();
            ServiceRequestHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.body = new JoinRequest();
            JoinRequestConverter.BinaryReadRecursive(meta, binaryData, obj.body, baseOff + 268);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, JoinRequestPacket obj)
        {
            ServiceRequestHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            JoinRequestConverter.BinaryWriteRecursive(parentOff + 268, writer, allocator, obj.body);
        }
    }
}
