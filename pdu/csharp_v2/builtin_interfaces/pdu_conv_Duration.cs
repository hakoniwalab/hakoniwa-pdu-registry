using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;

namespace Hakoniwa.Pdu.CSharpV2.builtin_interfaces
{
    public static class DurationConverter
    {
        public static Duration PduToMsg(byte[] binaryData)
        {
            var obj = new Duration();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Duration obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Duration obj, int baseOff)
        {
            obj.sec = PduRuntime.ReadInt32(binaryData, baseOff + 0);
            obj.nanosec = PduRuntime.ReadUInt32(binaryData, baseOff + 4);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Duration obj)
        {
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.sec), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.nanosec), parentOff + 4);
        }
    }
}
