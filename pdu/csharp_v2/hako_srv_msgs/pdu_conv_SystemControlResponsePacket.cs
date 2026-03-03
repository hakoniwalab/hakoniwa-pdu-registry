using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class SystemControlResponsePacketConverter
    {
        public static SystemControlResponsePacket PduToMsg(byte[] binaryData)
        {
            var obj = new SystemControlResponsePacket();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(SystemControlResponsePacket obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, SystemControlResponsePacket obj, int baseOff)
        {
            obj.header = new ServiceResponseHeader();
            ServiceResponseHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.body = new SystemControlResponse();
            SystemControlResponseConverter.BinaryReadRecursive(meta, binaryData, obj.body, baseOff + 268);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, SystemControlResponsePacket obj)
        {
            ServiceResponseHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            SystemControlResponseConverter.BinaryWriteRecursive(parentOff + 268, writer, allocator, obj.body);
        }
    }
}
