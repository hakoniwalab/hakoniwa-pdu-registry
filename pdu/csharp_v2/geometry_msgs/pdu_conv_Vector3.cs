using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class Vector3Converter
    {
        public static Vector3 PduToMsg(byte[] binaryData)
        {
            var obj = new Vector3();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Vector3 obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Vector3 obj, int baseOff)
        {
            obj.x = PduRuntime.ReadFloat64(binaryData, baseOff + 0);
            obj.y = PduRuntime.ReadFloat64(binaryData, baseOff + 8);
            obj.z = PduRuntime.ReadFloat64(binaryData, baseOff + 16);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Vector3 obj)
        {
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.x), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.y), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.z), parentOff + 16);
        }
    }
}
