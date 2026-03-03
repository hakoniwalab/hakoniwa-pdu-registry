using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.drone_srv_msgs;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public static class LiDARScanResponseConverter
    {
        public static LiDARScanResponse PduToMsg(byte[] binaryData)
        {
            var obj = new LiDARScanResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(LiDARScanResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, LiDARScanResponse obj, int baseOff)
        {
            obj.ok = PduRuntime.ReadBool(binaryData, baseOff + 0);
            obj.point_cloud = new PointCloud2();
            PointCloud2Converter.BinaryReadRecursive(meta, binaryData, obj.point_cloud, baseOff + 4);
            obj.lidar_pose = new Pose();
            PoseConverter.BinaryReadRecursive(meta, binaryData, obj.lidar_pose, baseOff + 184);
            obj.message = PduRuntime.ReadString(binaryData, baseOff + 240, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, LiDARScanResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForBool(obj.ok), parentOff + 0);
            PointCloud2Converter.BinaryWriteRecursive(parentOff + 4, writer, allocator, obj.point_cloud);
            PoseConverter.BinaryWriteRecursive(parentOff + 184, writer, allocator, obj.lidar_pose);
            allocator.Add(PduRuntime.GetBinaryForString(obj.message, 128), parentOff + 240);
        }
    }
}
