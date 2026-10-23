using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class RenderCameraResponseConverter
    {
        public static RenderCameraResponse PduToMsg(byte[] binaryData)
        {
            var obj = new RenderCameraResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(RenderCameraResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, RenderCameraResponse obj, int baseOff)
        {
            obj.result_code = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.sim_time_usec = PduRuntime.ReadUInt64(binaryData, baseOff + 8);
            obj.image = new Image();
            ImageConverter.BinaryReadRecursive(meta, binaryData, obj.image, baseOff + 16);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, RenderCameraResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.result_code), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.sim_time_usec), parentOff + 8);
            ImageConverter.BinaryWriteRecursive(parentOff + 16, writer, allocator, obj.image);
        }
    }
}
