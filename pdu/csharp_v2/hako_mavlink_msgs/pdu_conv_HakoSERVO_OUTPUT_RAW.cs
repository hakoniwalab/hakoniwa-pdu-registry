using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public static class HakoSERVO_OUTPUT_RAWConverter
    {
        public static HakoSERVO_OUTPUT_RAW PduToMsg(byte[] binaryData)
        {
            var obj = new HakoSERVO_OUTPUT_RAW();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoSERVO_OUTPUT_RAW obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoSERVO_OUTPUT_RAW obj, int baseOff)
        {
            obj.time_usec = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.port = PduRuntime.ReadUInt8(binaryData, baseOff + 4);
            obj.servo1_raw = PduRuntime.ReadUInt16(binaryData, baseOff + 6);
            obj.servo2_raw = PduRuntime.ReadUInt16(binaryData, baseOff + 8);
            obj.servo3_raw = PduRuntime.ReadUInt16(binaryData, baseOff + 10);
            obj.servo4_raw = PduRuntime.ReadUInt16(binaryData, baseOff + 12);
            obj.servo5_raw = PduRuntime.ReadUInt16(binaryData, baseOff + 14);
            obj.servo6_raw = PduRuntime.ReadUInt16(binaryData, baseOff + 16);
            obj.servo7_raw = PduRuntime.ReadUInt16(binaryData, baseOff + 18);
            obj.servo8_raw = PduRuntime.ReadUInt16(binaryData, baseOff + 20);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoSERVO_OUTPUT_RAW obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.time_usec), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.port), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.servo1_raw), parentOff + 6);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.servo2_raw), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.servo3_raw), parentOff + 10);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.servo4_raw), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.servo5_raw), parentOff + 14);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.servo6_raw), parentOff + 16);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.servo7_raw), parentOff + 18);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.servo8_raw), parentOff + 20);
        }
    }
}
