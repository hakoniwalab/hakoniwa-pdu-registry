using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class AckEventRequestConverter
    {
        public static AckEventRequest PduToMsg(byte[] binaryData)
        {
            var obj = new AckEventRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AckEventRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AckEventRequest obj, int baseOff)
        {
            obj.name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.event_code = PduRuntime.ReadUInt32(binaryData, baseOff + 128);
            obj.result_code = PduRuntime.ReadUInt32(binaryData, baseOff + 132);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AckEventRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.name, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.event_code), parentOff + 128);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.result_code), parentOff + 132);
        }
    }
}
