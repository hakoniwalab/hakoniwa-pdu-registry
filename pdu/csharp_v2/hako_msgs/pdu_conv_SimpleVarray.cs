using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class SimpleVarrayConverter
    {
        public static SimpleVarray PduToMsg(byte[] binaryData)
        {
            var obj = new SimpleVarray();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(SimpleVarray obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, SimpleVarray obj, int baseOff)
        {
            obj.data = new List<sbyte>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 0);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 0 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.data.Add(PduRuntime.ReadInt8(binaryData, meta.HeapOff + offsetFromHeap + (i * 1)));
                }
            }
            obj.fixed_array = new List<sbyte>();
            for (var i = 0; i < 10; i++) {
                obj.fixed_array.Add(PduRuntime.ReadInt8(binaryData, baseOff + 8 + (i * 1)));
            }
            obj.p_mem1 = PduRuntime.ReadInt32(binaryData, baseOff + 20);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, SimpleVarray obj)
        {
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.data.Count), parentOff + 0);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 0 + 4);
                for (var i = 0; i < obj.data.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForInt8(obj.data[i]));
                }
            }
            for (var i = 0; i < obj.fixed_array.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForInt8(obj.fixed_array[i]), parentOff + 8 + (i * 1));
            }
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.p_mem1), parentOff + 20);
        }
    }
}
