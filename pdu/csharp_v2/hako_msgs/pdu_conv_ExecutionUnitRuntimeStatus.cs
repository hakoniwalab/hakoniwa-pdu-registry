using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class ExecutionUnitRuntimeStatusConverter
    {
        public static ExecutionUnitRuntimeStatus PduToMsg(byte[] binaryData)
        {
            var obj = new ExecutionUnitRuntimeStatus();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ExecutionUnitRuntimeStatus obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ExecutionUnitRuntimeStatus obj, int baseOff)
        {
            obj.config_hash = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.unit_count = PduRuntime.ReadUInt16(binaryData, baseOff + 4);
            obj.status = new List<byte>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 8);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 8 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.status.Add(PduRuntime.ReadUInt8(binaryData, meta.HeapOff + offsetFromHeap + (i * 1)));
                }
            }
            obj.epoch = new List<byte>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 16);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 16 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.epoch.Add(PduRuntime.ReadUInt8(binaryData, meta.HeapOff + offsetFromHeap + (i * 1)));
                }
            }
            obj.curr_owner_node_id = new List<byte>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 24);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 24 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.curr_owner_node_id.Add(PduRuntime.ReadUInt8(binaryData, meta.HeapOff + offsetFromHeap + (i * 1)));
                }
            }
            obj.next_owner_node_id = new List<byte>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 32);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 32 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.next_owner_node_id.Add(PduRuntime.ReadUInt8(binaryData, meta.HeapOff + offsetFromHeap + (i * 1)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ExecutionUnitRuntimeStatus obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.config_hash), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.unit_count), parentOff + 4);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.status.Count), parentOff + 8);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 8 + 4);
                for (var i = 0; i < obj.status.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForUInt8(obj.status[i]));
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.epoch.Count), parentOff + 16);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 16 + 4);
                for (var i = 0; i < obj.epoch.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForUInt8(obj.epoch[i]));
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.curr_owner_node_id.Count), parentOff + 24);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 24 + 4);
                for (var i = 0; i < obj.curr_owner_node_id.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForUInt8(obj.curr_owner_node_id[i]));
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.next_owner_node_id.Count), parentOff + 32);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 32 + 4);
                for (var i = 0; i < obj.next_owner_node_id.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForUInt8(obj.next_owner_node_id[i]));
                }
            }
        }
    }
}
