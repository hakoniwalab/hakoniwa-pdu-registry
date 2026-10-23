using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class RenderCameraFrameResponseConverter
    {
        public static RenderCameraFrameResponse PduToMsg(byte[] binaryData)
        {
            var obj = new RenderCameraFrameResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(RenderCameraFrameResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, RenderCameraFrameResponse obj, int baseOff)
        {
            obj.result_code = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.sim_time_usec = PduRuntime.ReadUInt64(binaryData, baseOff + 8);
            obj.rgb = new Image();
            ImageConverter.BinaryReadRecursive(meta, binaryData, obj.rgb, baseOff + 16);
            obj.depth = new Image();
            ImageConverter.BinaryReadRecursive(meta, binaryData, obj.depth, baseOff + 304);
            obj.segmentation = new Image();
            ImageConverter.BinaryReadRecursive(meta, binaryData, obj.segmentation, baseOff + 592);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, RenderCameraFrameResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.result_code), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.sim_time_usec), parentOff + 8);
            ImageConverter.BinaryWriteRecursive(parentOff + 16, writer, allocator, obj.rgb);
            ImageConverter.BinaryWriteRecursive(parentOff + 304, writer, allocator, obj.depth);
            ImageConverter.BinaryWriteRecursive(parentOff + 592, writer, allocator, obj.segmentation);
        }
    }
}
