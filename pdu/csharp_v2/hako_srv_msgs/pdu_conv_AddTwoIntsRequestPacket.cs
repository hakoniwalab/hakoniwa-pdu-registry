using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class AddTwoIntsRequestPacketConverter
    {
        public static AddTwoIntsRequestPacket PduToMsg(byte[] binaryData)
        {
            var obj = new AddTwoIntsRequestPacket();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AddTwoIntsRequestPacket obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AddTwoIntsRequestPacket obj, int baseOff)
        {
            obj.header = new ServiceRequestHeader();
            ServiceRequestHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.body = new AddTwoIntsRequest();
            AddTwoIntsRequestConverter.BinaryReadRecursive(meta, binaryData, obj.body, baseOff + 272);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AddTwoIntsRequestPacket obj)
        {
            ServiceRequestHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            AddTwoIntsRequestConverter.BinaryWriteRecursive(parentOff + 272, writer, allocator, obj.body);
        }
    }
}
