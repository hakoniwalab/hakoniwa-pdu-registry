using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.std_msgs
{
    public static class UInt8MultiArrayConverter
    {
        public static UInt8MultiArray PduToMsg(byte[] binaryData)
        {
            var obj = new UInt8MultiArray();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(UInt8MultiArray obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, UInt8MultiArray obj, int baseOff)
        {
            obj.layout = new MultiArrayLayout();
            MultiArrayLayoutConverter.BinaryReadRecursive(meta, binaryData, obj.layout, baseOff + 0);
            obj.data = new List<byte>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 12);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 12 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.data.Add(PduRuntime.ReadUInt8(binaryData, meta.HeapOff + offsetFromHeap + (i * 1)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, UInt8MultiArray obj)
        {
            MultiArrayLayoutConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.layout);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.data.Count), parentOff + 12);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 12 + 4);
                for (var i = 0; i < obj.data.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForUInt8(obj.data[i]));
                }
            }
        }
    }
}
