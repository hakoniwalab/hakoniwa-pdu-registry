using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class DroneVisualStateArrayConverter
    {
        public static DroneVisualStateArray PduToMsg(byte[] binaryData)
        {
            var obj = new DroneVisualStateArray();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(DroneVisualStateArray obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, DroneVisualStateArray obj, int baseOff)
        {
            obj.sequence_id = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.chunk_index = PduRuntime.ReadUInt32(binaryData, baseOff + 4);
            obj.chunk_count = PduRuntime.ReadUInt32(binaryData, baseOff + 8);
            obj.start_index = PduRuntime.ReadUInt32(binaryData, baseOff + 12);
            obj.valid_count = PduRuntime.ReadUInt32(binaryData, baseOff + 16);
            obj.drones = new List<DroneVisualState>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 20);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 20 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new DroneVisualState();
                    DroneVisualStateConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 32));
                    obj.drones.Add(tmp);
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, DroneVisualStateArray obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.sequence_id), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.chunk_index), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.chunk_count), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.start_index), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.valid_count), parentOff + 16);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.drones.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 20);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 20 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 32], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    DroneVisualStateConverter.BinaryWriteRecursive(offsetFromHeap + (i * 32), writer, writer.HeapAllocator, obj.drones[i]);
                }
            }
        }
    }
}
