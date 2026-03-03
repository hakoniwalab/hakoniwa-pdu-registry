using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class ExecutionUnitRuntimeContextConverter
    {
        public static ExecutionUnitRuntimeContext PduToMsg(byte[] binaryData)
        {
            var obj = new ExecutionUnitRuntimeContext();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ExecutionUnitRuntimeContext obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ExecutionUnitRuntimeContext obj, int baseOff)
        {
            obj.config_hash = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.epoch = PduRuntime.ReadUInt8(binaryData, baseOff + 4);
            obj.owner_id = PduRuntime.ReadUInt8(binaryData, baseOff + 5);
            obj.context = new List<byte>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 8);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 8 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.context.Add(PduRuntime.ReadUInt8(binaryData, meta.HeapOff + offsetFromHeap + (i * 1)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ExecutionUnitRuntimeContext obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.config_hash), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.epoch), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.owner_id), parentOff + 5);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.context.Count), parentOff + 8);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 8 + 4);
                for (var i = 0; i < obj.context.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForUInt8(obj.context[i]));
                }
            }
        }
    }
}
