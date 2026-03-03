using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class HakoBatteryStatusConverter
    {
        public static HakoBatteryStatus PduToMsg(byte[] binaryData)
        {
            var obj = new HakoBatteryStatus();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoBatteryStatus obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoBatteryStatus obj, int baseOff)
        {
            obj.full_voltage = PduRuntime.ReadFloat64(binaryData, baseOff + 0);
            obj.curr_voltage = PduRuntime.ReadFloat64(binaryData, baseOff + 8);
            obj.curr_temp = PduRuntime.ReadFloat64(binaryData, baseOff + 16);
            obj.status = PduRuntime.ReadUInt32(binaryData, baseOff + 24);
            obj.cycles = PduRuntime.ReadUInt32(binaryData, baseOff + 28);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoBatteryStatus obj)
        {
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.full_voltage), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.curr_voltage), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.curr_temp), parentOff + 16);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.status), parentOff + 24);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.cycles), parentOff + 28);
        }
    }
}
