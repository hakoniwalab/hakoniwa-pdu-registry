using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class HakoCmdCameraConverter
    {
        public static HakoCmdCamera PduToMsg(byte[] binaryData)
        {
            var obj = new HakoCmdCamera();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoCmdCamera obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoCmdCamera obj, int baseOff)
        {
            obj.header = new HakoCmdHeader();
            HakoCmdHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.request_id = PduRuntime.ReadInt32(binaryData, baseOff + 12);
            obj.encode_type = PduRuntime.ReadInt32(binaryData, baseOff + 16);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoCmdCamera obj)
        {
            HakoCmdHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.request_id), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.encode_type), parentOff + 16);
        }
    }
}
