using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class PoseArrayConverter
    {
        public static PoseArray PduToMsg(byte[] binaryData)
        {
            var obj = new PoseArray();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(PoseArray obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, PoseArray obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.poses = new List<Pose>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 136);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 136 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new Pose();
                    PoseConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 56));
                    obj.poses.Add(tmp);
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, PoseArray obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.poses.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 136);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 136 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 56], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    PoseConverter.BinaryWriteRecursive(offsetFromHeap + (i * 56), writer, writer.HeapAllocator, obj.poses[i]);
                }
            }
        }
    }
}
