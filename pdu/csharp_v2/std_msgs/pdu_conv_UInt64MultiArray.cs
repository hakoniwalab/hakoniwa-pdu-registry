using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public static class UInt64MultiArrayConverter
    {
        public static UInt64MultiArray PduToMsg(byte[] binaryData)
        {
            var obj = new UInt64MultiArray();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(UInt64MultiArray obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, UInt64MultiArray obj, int baseOff)
        {
            obj.layout = new MultiArrayLayout();
            MultiArrayLayoutConverter.BinaryReadRecursive(meta, binaryData, obj.layout, baseOff + 0);
            obj.data = new List<ulong>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 12);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 12 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.data.Add(PduRuntime.ReadUInt64(binaryData, meta.HeapOff + offsetFromHeap + (i * 8)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, UInt64MultiArray obj)
        {
            MultiArrayLayoutConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.layout);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.data.Count), parentOff + 12);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 12 + 4);
                for (var i = 0; i < obj.data.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForUInt64(obj.data[i]));
                }
            }
        }
    }
}
