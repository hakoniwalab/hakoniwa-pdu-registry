using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class RenderCameraRequestConverter
    {
        public static RenderCameraRequest PduToMsg(byte[] binaryData)
        {
            var obj = new RenderCameraRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(RenderCameraRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, RenderCameraRequest obj, int baseOff)
        {
            obj.camera_name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.sim_time_usec = PduRuntime.ReadUInt64(binaryData, baseOff + 128);
            obj.camera_pose = new Pose();
            PoseConverter.BinaryReadRecursive(meta, binaryData, obj.camera_pose, baseOff + 136);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, RenderCameraRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.camera_name, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.sim_time_usec), parentOff + 128);
            PoseConverter.BinaryWriteRecursive(parentOff + 136, writer, allocator, obj.camera_pose);
        }
    }
}
