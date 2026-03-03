using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class TransformStampedConverter
    {
        public static TransformStamped PduToMsg(byte[] binaryData)
        {
            var obj = new TransformStamped();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(TransformStamped obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, TransformStamped obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.child_frame_id = PduRuntime.ReadString(binaryData, baseOff + 136, 128);
            obj.transform = new Transform();
            TransformConverter.BinaryReadRecursive(meta, binaryData, obj.transform, baseOff + 264);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, TransformStamped obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForString(obj.child_frame_id, 128), parentOff + 136);
            TransformConverter.BinaryWriteRecursive(parentOff + 264, writer, allocator, obj.transform);
        }
    }
}
