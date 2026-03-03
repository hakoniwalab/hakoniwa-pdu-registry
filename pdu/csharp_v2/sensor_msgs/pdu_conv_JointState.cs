using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class JointStateConverter
    {
        public static JointState PduToMsg(byte[] binaryData)
        {
            var obj = new JointState();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(JointState obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, JointState obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.name = new List<string>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 136);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 136 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.name.Add(PduRuntime.ReadString(binaryData, meta.HeapOff + offsetFromHeap + (i * 128), 128));
                }
            }
            obj.position = new List<double>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 144);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 144 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.position.Add(PduRuntime.ReadFloat64(binaryData, meta.HeapOff + offsetFromHeap + (i * 8)));
                }
            }
            obj.velocity = new List<double>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 152);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 152 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.velocity.Add(PduRuntime.ReadFloat64(binaryData, meta.HeapOff + offsetFromHeap + (i * 8)));
                }
            }
            obj.effort = new List<double>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 160);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 160 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.effort.Add(PduRuntime.ReadFloat64(binaryData, meta.HeapOff + offsetFromHeap + (i * 8)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, JointState obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.name.Count), parentOff + 136);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 136 + 4);
                for (var i = 0; i < obj.name.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForString(obj.name[i], 128));
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.position.Count), parentOff + 144);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 144 + 4);
                for (var i = 0; i < obj.position.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat64(obj.position[i]));
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.velocity.Count), parentOff + 152);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 152 + 4);
                for (var i = 0; i < obj.velocity.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat64(obj.velocity[i]));
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.effort.Count), parentOff + 160);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 160 + 4);
                for (var i = 0; i < obj.effort.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat64(obj.effort[i]));
                }
            }
        }
    }
}
