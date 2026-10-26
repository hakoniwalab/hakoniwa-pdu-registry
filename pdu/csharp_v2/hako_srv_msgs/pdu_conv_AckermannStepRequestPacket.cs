using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class AckermannStepRequestPacketConverter
    {
        public static AckermannStepRequestPacket PduToMsg(byte[] binaryData)
        {
            var obj = new AckermannStepRequestPacket();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AckermannStepRequestPacket obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AckermannStepRequestPacket obj, int baseOff)
        {
            obj.header = new ServiceRequestHeader();
            ServiceRequestHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.body = new AckermannStepRequest();
            AckermannStepRequestConverter.BinaryReadRecursive(meta, binaryData, obj.body, baseOff + 272);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AckermannStepRequestPacket obj)
        {
            ServiceRequestHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            AckermannStepRequestConverter.BinaryWriteRecursive(parentOff + 272, writer, allocator, obj.body);
        }
    }
}
