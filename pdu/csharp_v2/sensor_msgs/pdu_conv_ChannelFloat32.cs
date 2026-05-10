using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class ChannelFloat32Converter
    {
        public static ChannelFloat32 PduToMsg(byte[] binaryData)
        {
            var obj = new ChannelFloat32();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ChannelFloat32 obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ChannelFloat32 obj, int baseOff)
        {
            obj.name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.values = new List<float>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 128);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 128 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.values.Add(PduRuntime.ReadFloat32(binaryData, meta.HeapOff + offsetFromHeap + (i * 4)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ChannelFloat32 obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.name, 128), parentOff + 0);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.values.Count), parentOff + 128);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 128 + 4);
                for (var i = 0; i < obj.values.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat32(obj.values[i]));
                }
            }
        }
    }
}
