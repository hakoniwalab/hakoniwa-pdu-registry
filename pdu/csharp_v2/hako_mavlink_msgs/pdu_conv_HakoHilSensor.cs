using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public static class HakoHilSensorConverter
    {
        public static HakoHilSensor PduToMsg(byte[] binaryData)
        {
            var obj = new HakoHilSensor();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoHilSensor obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoHilSensor obj, int baseOff)
        {
            obj.time_usec = PduRuntime.ReadUInt64(binaryData, baseOff + 0);
            obj.xacc = PduRuntime.ReadFloat32(binaryData, baseOff + 8);
            obj.yacc = PduRuntime.ReadFloat32(binaryData, baseOff + 12);
            obj.zacc = PduRuntime.ReadFloat32(binaryData, baseOff + 16);
            obj.xgyro = PduRuntime.ReadFloat32(binaryData, baseOff + 20);
            obj.ygyro = PduRuntime.ReadFloat32(binaryData, baseOff + 24);
            obj.zgyro = PduRuntime.ReadFloat32(binaryData, baseOff + 28);
            obj.xmag = PduRuntime.ReadFloat32(binaryData, baseOff + 32);
            obj.ymag = PduRuntime.ReadFloat32(binaryData, baseOff + 36);
            obj.zmag = PduRuntime.ReadFloat32(binaryData, baseOff + 40);
            obj.abs_pressure = PduRuntime.ReadFloat32(binaryData, baseOff + 44);
            obj.diff_pressure = PduRuntime.ReadFloat32(binaryData, baseOff + 48);
            obj.pressure_alt = PduRuntime.ReadFloat32(binaryData, baseOff + 52);
            obj.temperature = PduRuntime.ReadFloat32(binaryData, baseOff + 56);
            obj.fields_updated = PduRuntime.ReadUInt32(binaryData, baseOff + 60);
            obj.id = PduRuntime.ReadUInt8(binaryData, baseOff + 64);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoHilSensor obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.time_usec), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.xacc), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.yacc), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.zacc), parentOff + 16);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.xgyro), parentOff + 20);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.ygyro), parentOff + 24);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.zgyro), parentOff + 28);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.xmag), parentOff + 32);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.ymag), parentOff + 36);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.zmag), parentOff + 40);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.abs_pressure), parentOff + 44);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.diff_pressure), parentOff + 48);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.pressure_alt), parentOff + 52);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.temperature), parentOff + 56);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.fields_updated), parentOff + 60);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.id), parentOff + 64);
        }
    }
}
