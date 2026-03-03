using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public static class MultiArrayLayoutConverter
    {
        public static MultiArrayLayout PduToMsg(byte[] binaryData)
        {
            var obj = new MultiArrayLayout();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(MultiArrayLayout obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, MultiArrayLayout obj, int baseOff)
        {
            obj.dim = new List<MultiArrayDimension>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 0);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 0 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new MultiArrayDimension();
                    MultiArrayDimensionConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 136));
                    obj.dim.Add(tmp);
                }
            }
            obj.data_offset = PduRuntime.ReadUInt32(binaryData, baseOff + 8);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, MultiArrayLayout obj)
        {
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.dim.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 0);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 0 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 136], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    MultiArrayDimensionConverter.BinaryWriteRecursive(offsetFromHeap + (i * 136), writer, writer.HeapAllocator, obj.dim[i]);
                }
            }
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.data_offset), parentOff + 8);
        }
    }
}
