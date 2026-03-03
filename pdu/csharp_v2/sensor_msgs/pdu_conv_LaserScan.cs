using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class LaserScanConverter
    {
        public static LaserScan PduToMsg(byte[] binaryData)
        {
            var obj = new LaserScan();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(LaserScan obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, LaserScan obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.angle_min = PduRuntime.ReadFloat32(binaryData, baseOff + 136);
            obj.angle_max = PduRuntime.ReadFloat32(binaryData, baseOff + 140);
            obj.angle_increment = PduRuntime.ReadFloat32(binaryData, baseOff + 144);
            obj.time_increment = PduRuntime.ReadFloat32(binaryData, baseOff + 148);
            obj.scan_time = PduRuntime.ReadFloat32(binaryData, baseOff + 152);
            obj.range_min = PduRuntime.ReadFloat32(binaryData, baseOff + 156);
            obj.range_max = PduRuntime.ReadFloat32(binaryData, baseOff + 160);
            obj.ranges = new List<float>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 164);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 164 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.ranges.Add(PduRuntime.ReadFloat32(binaryData, meta.HeapOff + offsetFromHeap + (i * 4)));
                }
            }
            obj.intensities = new List<float>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 172);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 172 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.intensities.Add(PduRuntime.ReadFloat32(binaryData, meta.HeapOff + offsetFromHeap + (i * 4)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, LaserScan obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.angle_min), parentOff + 136);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.angle_max), parentOff + 140);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.angle_increment), parentOff + 144);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.time_increment), parentOff + 148);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.scan_time), parentOff + 152);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.range_min), parentOff + 156);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.range_max), parentOff + 160);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.ranges.Count), parentOff + 164);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 164 + 4);
                for (var i = 0; i < obj.ranges.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat32(obj.ranges[i]));
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.intensities.Count), parentOff + 172);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 172 + 4);
                for (var i = 0; i < obj.intensities.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat32(obj.intensities[i]));
                }
            }
        }
    }
}
