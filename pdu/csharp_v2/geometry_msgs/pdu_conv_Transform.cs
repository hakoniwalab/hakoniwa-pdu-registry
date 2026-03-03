using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class TransformConverter
    {
        public static Transform PduToMsg(byte[] binaryData)
        {
            var obj = new Transform();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Transform obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Transform obj, int baseOff)
        {
            obj.translation = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.translation, baseOff + 0);
            obj.rotation = new Quaternion();
            QuaternionConverter.BinaryReadRecursive(meta, binaryData, obj.rotation, baseOff + 24);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Transform obj)
        {
            Vector3Converter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.translation);
            QuaternionConverter.BinaryWriteRecursive(parentOff + 24, writer, allocator, obj.rotation);
        }
    }
}
