using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class MonitorCameraDataConverter
    {
        public static MonitorCameraData PduToMsg(byte[] binaryData)
        {
            var obj = new MonitorCameraData();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(MonitorCameraData obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, MonitorCameraData obj, int baseOff)
        {
            obj.request_id = PduRuntime.ReadInt32(binaryData, baseOff + 0);
            obj.image_data_length = PduRuntime.ReadInt32(binaryData, baseOff + 4);
            obj.image = new CompressedImage();
            CompressedImageConverter.BinaryReadRecursive(meta, binaryData, obj.image, baseOff + 8);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, MonitorCameraData obj)
        {
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.request_id), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.image_data_length), parentOff + 4);
            CompressedImageConverter.BinaryWriteRecursive(parentOff + 8, writer, allocator, obj.image);
        }
    }
}
