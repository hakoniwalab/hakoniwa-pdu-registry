using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class RegisterClientResponseConverter
    {
        public static RegisterClientResponse PduToMsg(byte[] binaryData)
        {
            var obj = new RegisterClientResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(RegisterClientResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, RegisterClientResponse obj, int baseOff)
        {
            obj.service_id = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.client_id = PduRuntime.ReadUInt32(binaryData, baseOff + 4);
            obj.request_channel_id = PduRuntime.ReadUInt32(binaryData, baseOff + 8);
            obj.response_channel_id = PduRuntime.ReadUInt32(binaryData, baseOff + 12);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, RegisterClientResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.service_id), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.client_id), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.request_channel_id), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.response_channel_id), parentOff + 12);
        }
    }
}
