using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public static class HakoSystemTimeConverter
    {
        public static HakoSystemTime PduToMsg(byte[] binaryData)
        {
            var obj = new HakoSystemTime();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoSystemTime obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoSystemTime obj, int baseOff)
        {
            obj.time_unix_usec = PduRuntime.ReadUInt64(binaryData, baseOff + 0);
            obj.time_boot_ms = PduRuntime.ReadUInt64(binaryData, baseOff + 8);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoSystemTime obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.time_unix_usec), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.time_boot_ms), parentOff + 8);
        }
    }
}
