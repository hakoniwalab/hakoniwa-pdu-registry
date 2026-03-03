using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public static class HakoGLOBAL_POSITION_INTConverter
    {
        public static HakoGLOBAL_POSITION_INT PduToMsg(byte[] binaryData)
        {
            var obj = new HakoGLOBAL_POSITION_INT();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoGLOBAL_POSITION_INT obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoGLOBAL_POSITION_INT obj, int baseOff)
        {
            obj.time_boot_ms = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.lat = PduRuntime.ReadInt32(binaryData, baseOff + 4);
            obj.lon = PduRuntime.ReadInt32(binaryData, baseOff + 8);
            obj.alt = PduRuntime.ReadInt32(binaryData, baseOff + 12);
            obj.relative_alt = PduRuntime.ReadInt32(binaryData, baseOff + 16);
            obj.vx = PduRuntime.ReadInt16(binaryData, baseOff + 20);
            obj.vy = PduRuntime.ReadInt16(binaryData, baseOff + 22);
            obj.vz = PduRuntime.ReadInt16(binaryData, baseOff + 24);
            obj.hdg = PduRuntime.ReadUInt16(binaryData, baseOff + 26);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoGLOBAL_POSITION_INT obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.time_boot_ms), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.lat), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.lon), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.alt), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.relative_alt), parentOff + 16);
            allocator.Add(PduRuntime.GetBinaryForInt16(obj.vx), parentOff + 20);
            allocator.Add(PduRuntime.GetBinaryForInt16(obj.vy), parentOff + 22);
            allocator.Add(PduRuntime.GetBinaryForInt16(obj.vz), parentOff + 24);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.hdg), parentOff + 26);
        }
    }
}
