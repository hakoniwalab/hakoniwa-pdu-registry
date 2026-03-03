using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.drone_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public static class CameraCaptureImageRequestConverter
    {
        public static CameraCaptureImageRequest PduToMsg(byte[] binaryData)
        {
            var obj = new CameraCaptureImageRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(CameraCaptureImageRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, CameraCaptureImageRequest obj, int baseOff)
        {
            obj.drone_name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.image_type = PduRuntime.ReadString(binaryData, baseOff + 128, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, CameraCaptureImageRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.drone_name, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForString(obj.image_type, 128), parentOff + 128);
        }
    }
}
