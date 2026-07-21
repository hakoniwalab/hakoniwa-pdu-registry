using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.trajectory_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.trajectory_msgs
{
    public static class JointTrajectoryConverter
    {
        public static JointTrajectory PduToMsg(byte[] binaryData)
        {
            var obj = new JointTrajectory();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(JointTrajectory obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, JointTrajectory obj, int baseOff)
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
            obj.points = new List<JointTrajectoryPoint>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 144);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 144 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new JointTrajectoryPoint();
                    JointTrajectoryPointConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 40));
                    obj.points.Add(tmp);
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, JointTrajectory obj)
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
                var arraySize = obj.points.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 144);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 144 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 40], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    JointTrajectoryPointConverter.BinaryWriteRecursive(offsetFromHeap + (i * 40), writer, writer.HeapAllocator, obj.points[i]);
                }
            }
        }
    }
}
