using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class DisturbanceBoundaryConverter
    {
        public static DisturbanceBoundary PduToMsg(byte[] binaryData)
        {
            var obj = new DisturbanceBoundary();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(DisturbanceBoundary obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, DisturbanceBoundary obj, int baseOff)
        {
            obj.boundary_point = new Point();
            PointConverter.BinaryReadRecursive(meta, binaryData, obj.boundary_point, baseOff + 0);
            obj.boundary_normal = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.boundary_normal, baseOff + 24);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, DisturbanceBoundary obj)
        {
            PointConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.boundary_point);
            Vector3Converter.BinaryWriteRecursive(parentOff + 24, writer, allocator, obj.boundary_normal);
        }
    }
}
