using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class PointConverter
    {
        public static Point PduToMsg(byte[] binaryData)
        {
            var obj = new Point();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Point obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Point obj, int baseOff)
        {
            obj.x = PduRuntime.ReadFloat64(binaryData, baseOff + 0);
            obj.y = PduRuntime.ReadFloat64(binaryData, baseOff + 8);
            obj.z = PduRuntime.ReadFloat64(binaryData, baseOff + 16);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Point obj)
        {
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.x), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.y), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.z), parentOff + 16);
        }
    }
}
