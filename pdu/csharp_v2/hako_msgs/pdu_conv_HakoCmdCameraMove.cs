using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class HakoCmdCameraMoveConverter
    {
        public static HakoCmdCameraMove PduToMsg(byte[] binaryData)
        {
            var obj = new HakoCmdCameraMove();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoCmdCameraMove obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoCmdCameraMove obj, int baseOff)
        {
            obj.header = new HakoCmdHeader();
            HakoCmdHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.request_id = PduRuntime.ReadInt32(binaryData, baseOff + 12);
            obj.angle = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.angle, baseOff + 16);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoCmdCameraMove obj)
        {
            HakoCmdHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.request_id), parentOff + 12);
            Vector3Converter.BinaryWriteRecursive(parentOff + 16, writer, allocator, obj.angle);
        }
    }
}
