using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sample_action_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sample_action_msgs
{
    public static class FibonacciFeedbackConverter
    {
        public static FibonacciFeedback PduToMsg(byte[] binaryData)
        {
            var obj = new FibonacciFeedback();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(FibonacciFeedback obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, FibonacciFeedback obj, int baseOff)
        {
            obj.partial_sequence = new List<int>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 0);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 0 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.partial_sequence.Add(PduRuntime.ReadInt32(binaryData, meta.HeapOff + offsetFromHeap + (i * 4)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, FibonacciFeedback obj)
        {
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.partial_sequence.Count), parentOff + 0);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 0 + 4);
                for (var i = 0; i < obj.partial_sequence.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForInt32(obj.partial_sequence[i]));
                }
            }
        }
    }
}
