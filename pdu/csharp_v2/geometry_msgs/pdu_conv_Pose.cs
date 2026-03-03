using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class PoseConverter
    {
        public static Pose PduToMsg(byte[] binaryData)
        {
            var obj = new Pose();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Pose obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Pose obj, int baseOff)
        {
            obj.position = new Point();
            PointConverter.BinaryReadRecursive(meta, binaryData, obj.position, baseOff + 0);
            obj.orientation = new Quaternion();
            QuaternionConverter.BinaryReadRecursive(meta, binaryData, obj.orientation, baseOff + 24);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Pose obj)
        {
            PointConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.position);
            QuaternionConverter.BinaryWriteRecursive(parentOff + 24, writer, allocator, obj.orientation);
        }
    }
}
