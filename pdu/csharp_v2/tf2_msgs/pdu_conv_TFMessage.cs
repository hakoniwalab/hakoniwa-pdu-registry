using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.tf2_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.tf2_msgs
{
    public static class TFMessageConverter
    {
        public static TFMessage PduToMsg(byte[] binaryData)
        {
            var obj = new TFMessage();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(TFMessage obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, TFMessage obj, int baseOff)
        {
            obj.transforms = new List<TransformStamped>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 0);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 0 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new TransformStamped();
                    TransformStampedConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 320));
                    obj.transforms.Add(tmp);
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, TFMessage obj)
        {
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.transforms.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 0);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 0 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 320], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    TransformStampedConverter.BinaryWriteRecursive(offsetFromHeap + (i * 320), writer, writer.HeapAllocator, obj.transforms[i]);
                }
            }
        }
    }
}
