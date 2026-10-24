using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class RenderCameraFrameRequestConverter
    {
        public static RenderCameraFrameRequest PduToMsg(byte[] binaryData)
        {
            var obj = new RenderCameraFrameRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(RenderCameraFrameRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, RenderCameraFrameRequest obj, int baseOff)
        {
            obj.camera_name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.sim_time_usec = PduRuntime.ReadUInt64(binaryData, baseOff + 128);
            obj.camera_pose = new Pose();
            PoseConverter.BinaryReadRecursive(meta, binaryData, obj.camera_pose, baseOff + 136);
            obj.outputs = PduRuntime.ReadUInt8(binaryData, baseOff + 192);
            obj.objects = new List<RenderObject>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 196);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 196 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new RenderObject();
                    RenderObjectConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 312));
                    obj.objects.Add(tmp);
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, RenderCameraFrameRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.camera_name, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.sim_time_usec), parentOff + 128);
            PoseConverter.BinaryWriteRecursive(parentOff + 136, writer, allocator, obj.camera_pose);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.outputs), parentOff + 192);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.objects.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 196);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 196 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 312], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    RenderObjectConverter.BinaryWriteRecursive(offsetFromHeap + (i * 312), writer, writer.HeapAllocator, obj.objects[i]);
                }
            }
        }
    }
}
