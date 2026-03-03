using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public static class HakoHilGpsConverter
    {
        public static HakoHilGps PduToMsg(byte[] binaryData)
        {
            var obj = new HakoHilGps();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoHilGps obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoHilGps obj, int baseOff)
        {
            obj.time_usec = PduRuntime.ReadUInt64(binaryData, baseOff + 0);
            obj.lat = PduRuntime.ReadInt32(binaryData, baseOff + 8);
            obj.lon = PduRuntime.ReadInt32(binaryData, baseOff + 12);
            obj.alt = PduRuntime.ReadInt32(binaryData, baseOff + 16);
            obj.eph = PduRuntime.ReadUInt16(binaryData, baseOff + 20);
            obj.epv = PduRuntime.ReadUInt16(binaryData, baseOff + 22);
            obj.vel = PduRuntime.ReadUInt16(binaryData, baseOff + 24);
            obj.vn = PduRuntime.ReadInt16(binaryData, baseOff + 26);
            obj.ve = PduRuntime.ReadInt16(binaryData, baseOff + 28);
            obj.vd = PduRuntime.ReadInt16(binaryData, baseOff + 30);
            obj.cog = PduRuntime.ReadUInt16(binaryData, baseOff + 32);
            obj.satellites_visible = PduRuntime.ReadUInt8(binaryData, baseOff + 34);
            obj.id = PduRuntime.ReadUInt8(binaryData, baseOff + 35);
            obj.yaw = PduRuntime.ReadUInt8(binaryData, baseOff + 36);
            obj.fix_type = PduRuntime.ReadUInt8(binaryData, baseOff + 37);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoHilGps obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.time_usec), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.lat), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.lon), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.alt), parentOff + 16);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.eph), parentOff + 20);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.epv), parentOff + 22);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.vel), parentOff + 24);
            allocator.Add(PduRuntime.GetBinaryForInt16(obj.vn), parentOff + 26);
            allocator.Add(PduRuntime.GetBinaryForInt16(obj.ve), parentOff + 28);
            allocator.Add(PduRuntime.GetBinaryForInt16(obj.vd), parentOff + 30);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.cog), parentOff + 32);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.satellites_visible), parentOff + 34);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.id), parentOff + 35);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.yaw), parentOff + 36);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.fix_type), parentOff + 37);
        }
    }
}
