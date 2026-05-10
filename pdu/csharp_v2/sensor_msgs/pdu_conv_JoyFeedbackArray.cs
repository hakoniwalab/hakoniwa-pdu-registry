using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class JoyFeedbackArrayConverter
    {
        public static JoyFeedbackArray PduToMsg(byte[] binaryData)
        {
            var obj = new JoyFeedbackArray();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(JoyFeedbackArray obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, JoyFeedbackArray obj, int baseOff)
        {
            obj.array = new List<JoyFeedback>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 0);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 0 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new JoyFeedback();
                    JoyFeedbackConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 8));
                    obj.array.Add(tmp);
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, JoyFeedbackArray obj)
        {
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.array.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 0);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 0 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 8], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    JoyFeedbackConverter.BinaryWriteRecursive(offsetFromHeap + (i * 8), writer, writer.HeapAllocator, obj.array[i]);
                }
            }
        }
    }
}
