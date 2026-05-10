using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class BatteryStateConverter
    {
        public static BatteryState PduToMsg(byte[] binaryData)
        {
            var obj = new BatteryState();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(BatteryState obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, BatteryState obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.voltage = PduRuntime.ReadFloat32(binaryData, baseOff + 136);
            obj.temperature = PduRuntime.ReadFloat32(binaryData, baseOff + 140);
            obj.current = PduRuntime.ReadFloat32(binaryData, baseOff + 144);
            obj.charge = PduRuntime.ReadFloat32(binaryData, baseOff + 148);
            obj.capacity = PduRuntime.ReadFloat32(binaryData, baseOff + 152);
            obj.design_capacity = PduRuntime.ReadFloat32(binaryData, baseOff + 156);
            obj.percentage = PduRuntime.ReadFloat32(binaryData, baseOff + 160);
            obj.power_supply_status = PduRuntime.ReadUInt8(binaryData, baseOff + 164);
            obj.power_supply_health = PduRuntime.ReadUInt8(binaryData, baseOff + 165);
            obj.power_supply_technology = PduRuntime.ReadUInt8(binaryData, baseOff + 166);
            obj.present = PduRuntime.ReadBool(binaryData, baseOff + 168);
            obj.cell_voltage = new List<float>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 172);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 172 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.cell_voltage.Add(PduRuntime.ReadFloat32(binaryData, meta.HeapOff + offsetFromHeap + (i * 4)));
                }
            }
            obj.cell_temperature = new List<float>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 180);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 180 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.cell_temperature.Add(PduRuntime.ReadFloat32(binaryData, meta.HeapOff + offsetFromHeap + (i * 4)));
                }
            }
            obj.location = PduRuntime.ReadString(binaryData, baseOff + 188, 128);
            obj.serial_number = PduRuntime.ReadString(binaryData, baseOff + 316, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, BatteryState obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.voltage), parentOff + 136);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.temperature), parentOff + 140);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.current), parentOff + 144);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.charge), parentOff + 148);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.capacity), parentOff + 152);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.design_capacity), parentOff + 156);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.percentage), parentOff + 160);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.power_supply_status), parentOff + 164);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.power_supply_health), parentOff + 165);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.power_supply_technology), parentOff + 166);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.present), parentOff + 168);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.cell_voltage.Count), parentOff + 172);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 172 + 4);
                for (var i = 0; i < obj.cell_voltage.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat32(obj.cell_voltage[i]));
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.cell_temperature.Count), parentOff + 180);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 180 + 4);
                for (var i = 0; i < obj.cell_temperature.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat32(obj.cell_temperature[i]));
                }
            }
            allocator.Add(PduRuntime.GetBinaryForString(obj.location, 128), parentOff + 188);
            allocator.Add(PduRuntime.GetBinaryForString(obj.serial_number, 128), parentOff + 316);
        }
    }
}
