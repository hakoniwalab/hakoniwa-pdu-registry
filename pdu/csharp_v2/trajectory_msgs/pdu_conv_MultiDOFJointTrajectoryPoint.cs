using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.trajectory_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;

namespace Hakoniwa.Pdu.CSharpV2.trajectory_msgs
{
    public static class MultiDOFJointTrajectoryPointConverter
    {
        public static MultiDOFJointTrajectoryPoint PduToMsg(byte[] binaryData)
        {
            var obj = new MultiDOFJointTrajectoryPoint();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(MultiDOFJointTrajectoryPoint obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, MultiDOFJointTrajectoryPoint obj, int baseOff)
        {
            obj.transforms = new List<Transform>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 0);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 0 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new Transform();
                    TransformConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 56));
                    obj.transforms.Add(tmp);
                }
            }
            obj.velocities = new List<Twist>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 8);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 8 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new Twist();
                    TwistConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 48));
                    obj.velocities.Add(tmp);
                }
            }
            obj.accelerations = new List<Twist>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 16);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 16 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new Twist();
                    TwistConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 48));
                    obj.accelerations.Add(tmp);
                }
            }
            obj.time_from_start = new Duration();
            DurationConverter.BinaryReadRecursive(meta, binaryData, obj.time_from_start, baseOff + 24);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, MultiDOFJointTrajectoryPoint obj)
        {
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.transforms.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 0);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 0 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 56], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    TransformConverter.BinaryWriteRecursive(offsetFromHeap + (i * 56), writer, writer.HeapAllocator, obj.transforms[i]);
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.velocities.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 8);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 8 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 48], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    TwistConverter.BinaryWriteRecursive(offsetFromHeap + (i * 48), writer, writer.HeapAllocator, obj.velocities[i]);
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.accelerations.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 16);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 16 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 48], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    TwistConverter.BinaryWriteRecursive(offsetFromHeap + (i * 48), writer, writer.HeapAllocator, obj.accelerations[i]);
                }
            }
            DurationConverter.BinaryWriteRecursive(parentOff + 24, writer, allocator, obj.time_from_start);
        }
    }
}
