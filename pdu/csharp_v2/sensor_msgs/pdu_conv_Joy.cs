using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class JoyConverter
    {
        public static Joy PduToMsg(byte[] binaryData)
        {
            var obj = new Joy();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Joy obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Joy obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.axes = new List<float>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 136);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 136 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.axes.Add(PduRuntime.ReadFloat32(binaryData, meta.HeapOff + offsetFromHeap + (i * 4)));
                }
            }
            obj.buttons = new List<int>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 144);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 144 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.buttons.Add(PduRuntime.ReadInt32(binaryData, meta.HeapOff + offsetFromHeap + (i * 4)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Joy obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.axes.Count), parentOff + 136);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 136 + 4);
                for (var i = 0; i < obj.axes.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat32(obj.axes[i]));
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.buttons.Count), parentOff + 144);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 144 + 4);
                for (var i = 0; i < obj.buttons.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForInt32(obj.buttons[i]));
                }
            }
        }
    }
}
