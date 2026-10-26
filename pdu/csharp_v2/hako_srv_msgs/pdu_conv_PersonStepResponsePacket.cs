using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class PersonStepResponsePacketConverter
    {
        public static PersonStepResponsePacket PduToMsg(byte[] binaryData)
        {
            var obj = new PersonStepResponsePacket();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(PersonStepResponsePacket obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, PersonStepResponsePacket obj, int baseOff)
        {
            obj.header = new ServiceResponseHeader();
            ServiceResponseHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.body = new PersonStepResponse();
            PersonStepResponseConverter.BinaryReadRecursive(meta, binaryData, obj.body, baseOff + 272);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, PersonStepResponsePacket obj)
        {
            ServiceResponseHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            PersonStepResponseConverter.BinaryWriteRecursive(parentOff + 272, writer, allocator, obj.body);
        }
    }
}
