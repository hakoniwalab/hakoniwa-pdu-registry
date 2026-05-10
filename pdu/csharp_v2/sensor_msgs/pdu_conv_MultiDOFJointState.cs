using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class MultiDOFJointStateConverter
    {
        public static MultiDOFJointState PduToMsg(byte[] binaryData)
        {
            var obj = new MultiDOFJointState();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(MultiDOFJointState obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, MultiDOFJointState obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.joint_names = new List<string>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 136);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 136 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.joint_names.Add(PduRuntime.ReadString(binaryData, meta.HeapOff + offsetFromHeap + (i * 128), 128));
                }
            }
            obj.transforms = new List<Transform>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 144);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 144 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new Transform();
                    TransformConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 56));
                    obj.transforms.Add(tmp);
                }
            }
            obj.twist = new List<Twist>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 152);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 152 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new Twist();
                    TwistConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 48));
                    obj.twist.Add(tmp);
                }
            }
            obj.wrench = new List<Wrench>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 160);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 160 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new Wrench();
                    WrenchConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 48));
                    obj.wrench.Add(tmp);
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, MultiDOFJointState obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.joint_names.Count), parentOff + 136);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 136 + 4);
                for (var i = 0; i < obj.joint_names.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForString(obj.joint_names[i], 128));
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.transforms.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 144);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 144 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 56], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    TransformConverter.BinaryWriteRecursive(offsetFromHeap + (i * 56), writer, writer.HeapAllocator, obj.transforms[i]);
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.twist.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 152);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 152 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 48], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    TwistConverter.BinaryWriteRecursive(offsetFromHeap + (i * 48), writer, writer.HeapAllocator, obj.twist[i]);
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.wrench.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 160);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 160 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 48], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    WrenchConverter.BinaryWriteRecursive(offsetFromHeap + (i * 48), writer, writer.HeapAllocator, obj.wrench[i]);
                }
            }
        }
    }
}
