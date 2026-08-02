using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sample_action_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sample_action_msgs
{
    public static class FibonacciResultConverter
    {
        public static FibonacciResult PduToMsg(byte[] binaryData)
        {
            var obj = new FibonacciResult();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(FibonacciResult obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, FibonacciResult obj, int baseOff)
        {
            obj.sequence = new List<int>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 0);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 0 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.sequence.Add(PduRuntime.ReadInt32(binaryData, meta.HeapOff + offsetFromHeap + (i * 4)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, FibonacciResult obj)
        {
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.sequence.Count), parentOff + 0);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 0 + 4);
                for (var i = 0; i < obj.sequence.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForInt32(obj.sequence[i]));
                }
            }
        }
    }
}
