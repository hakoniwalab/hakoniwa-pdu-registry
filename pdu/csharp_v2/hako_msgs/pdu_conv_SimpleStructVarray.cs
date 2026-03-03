using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class SimpleStructVarrayConverter
    {
        public static SimpleStructVarray PduToMsg(byte[] binaryData)
        {
            var obj = new SimpleStructVarray();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(SimpleStructVarray obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, SimpleStructVarray obj, int baseOff)
        {
            obj.aaa = PduRuntime.ReadInt32(binaryData, baseOff + 0);
            obj.fixed_str = new List<string>();
            for (var i = 0; i < 2; i++) {
                obj.fixed_str.Add(PduRuntime.ReadString(binaryData, baseOff + 4 + (i * 128), 128));
            }
            obj.varray_str = new List<string>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 260);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 260 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.varray_str.Add(PduRuntime.ReadString(binaryData, meta.HeapOff + offsetFromHeap + (i * 128), 128));
                }
            }
            obj.fixed_array = new List<SimpleVarray>();
            for (var i = 0; i < 5; i++) {
                var tmp = new SimpleVarray();
                SimpleVarrayConverter.BinaryReadRecursive(meta, binaryData, tmp, baseOff + 268 + (i * 24));
                obj.fixed_array.Add(tmp);
            }
            obj.data = new List<SimpleVarray>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 388);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 388 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new SimpleVarray();
                    SimpleVarrayConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 24));
                    obj.data.Add(tmp);
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, SimpleStructVarray obj)
        {
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.aaa), parentOff + 0);
            for (var i = 0; i < obj.fixed_str.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForString(obj.fixed_str[i], 128), parentOff + 4 + (i * 128));
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.varray_str.Count), parentOff + 260);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 260 + 4);
                for (var i = 0; i < obj.varray_str.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForString(obj.varray_str[i], 128));
                }
            }
            for (var i = 0; i < obj.fixed_array.Count; i++) {
                SimpleVarrayConverter.BinaryWriteRecursive(parentOff + 268 + (i * 24), writer, allocator, obj.fixed_array[i]);
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.data.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 388);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 388 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 24], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    SimpleVarrayConverter.BinaryWriteRecursive(offsetFromHeap + (i * 24), writer, writer.HeapAllocator, obj.data[i]);
                }
            }
        }
    }
}
