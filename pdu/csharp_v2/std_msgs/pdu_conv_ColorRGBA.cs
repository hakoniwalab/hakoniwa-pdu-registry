using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public static class ColorRGBAConverter
    {
        public static ColorRGBA PduToMsg(byte[] binaryData)
        {
            var obj = new ColorRGBA();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ColorRGBA obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ColorRGBA obj, int baseOff)
        {
            obj.r = PduRuntime.ReadFloat32(binaryData, baseOff + 0);
            obj.g = PduRuntime.ReadFloat32(binaryData, baseOff + 4);
            obj.b = PduRuntime.ReadFloat32(binaryData, baseOff + 8);
            obj.a = PduRuntime.ReadFloat32(binaryData, baseOff + 12);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ColorRGBA obj)
        {
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.r), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.g), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.b), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.a), parentOff + 12);
        }
    }
}
