using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class Point32Converter
    {
        public static Point32 PduToMsg(byte[] binaryData)
        {
            var obj = new Point32();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Point32 obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Point32 obj, int baseOff)
        {
            obj.x = PduRuntime.ReadFloat32(binaryData, baseOff + 0);
            obj.y = PduRuntime.ReadFloat32(binaryData, baseOff + 4);
            obj.z = PduRuntime.ReadFloat32(binaryData, baseOff + 8);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Point32 obj)
        {
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.x), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.y), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.z), parentOff + 8);
        }
    }
}
