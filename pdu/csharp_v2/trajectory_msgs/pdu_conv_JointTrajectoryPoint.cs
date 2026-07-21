using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.trajectory_msgs;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;

namespace Hakoniwa.Pdu.CSharpV2.trajectory_msgs
{
    public static class JointTrajectoryPointConverter
    {
        public static JointTrajectoryPoint PduToMsg(byte[] binaryData)
        {
            var obj = new JointTrajectoryPoint();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(JointTrajectoryPoint obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, JointTrajectoryPoint obj, int baseOff)
        {
            obj.positions = new List<double>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 0);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 0 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.positions.Add(PduRuntime.ReadFloat64(binaryData, meta.HeapOff + offsetFromHeap + (i * 8)));
                }
            }
            obj.velocities = new List<double>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 8);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 8 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.velocities.Add(PduRuntime.ReadFloat64(binaryData, meta.HeapOff + offsetFromHeap + (i * 8)));
                }
            }
            obj.accelerations = new List<double>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 16);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 16 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.accelerations.Add(PduRuntime.ReadFloat64(binaryData, meta.HeapOff + offsetFromHeap + (i * 8)));
                }
            }
            obj.effort = new List<double>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 24);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 24 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.effort.Add(PduRuntime.ReadFloat64(binaryData, meta.HeapOff + offsetFromHeap + (i * 8)));
                }
            }
            obj.time_from_start = new Duration();
            DurationConverter.BinaryReadRecursive(meta, binaryData, obj.time_from_start, baseOff + 32);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, JointTrajectoryPoint obj)
        {
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.positions.Count), parentOff + 0);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 0 + 4);
                for (var i = 0; i < obj.positions.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat64(obj.positions[i]));
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.velocities.Count), parentOff + 8);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 8 + 4);
                for (var i = 0; i < obj.velocities.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat64(obj.velocities[i]));
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.accelerations.Count), parentOff + 16);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 16 + 4);
                for (var i = 0; i < obj.accelerations.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat64(obj.accelerations[i]));
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.effort.Count), parentOff + 24);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 24 + 4);
                for (var i = 0; i < obj.effort.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat64(obj.effort[i]));
                }
            }
            DurationConverter.BinaryWriteRecursive(parentOff + 32, writer, allocator, obj.time_from_start);
        }
    }
}
