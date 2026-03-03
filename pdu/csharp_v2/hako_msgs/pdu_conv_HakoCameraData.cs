using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class HakoCameraDataConverter
    {
        public static HakoCameraData PduToMsg(byte[] binaryData)
        {
            var obj = new HakoCameraData();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoCameraData obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoCameraData obj, int baseOff)
        {
            obj.request_id = PduRuntime.ReadInt32(binaryData, baseOff + 0);
            obj.image = new CompressedImage();
            CompressedImageConverter.BinaryReadRecursive(meta, binaryData, obj.image, baseOff + 4);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoCameraData obj)
        {
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.request_id), parentOff + 0);
            CompressedImageConverter.BinaryWriteRecursive(parentOff + 4, writer, allocator, obj.image);
        }
    }
}
