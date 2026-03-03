using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.nav_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.nav_msgs
{
    public static class OdometryConverter
    {
        public static Odometry PduToMsg(byte[] binaryData)
        {
            var obj = new Odometry();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Odometry obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Odometry obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.child_frame_id = PduRuntime.ReadString(binaryData, baseOff + 136, 128);
            obj.pose = new PoseWithCovariance();
            PoseWithCovarianceConverter.BinaryReadRecursive(meta, binaryData, obj.pose, baseOff + 264);
            obj.twist = new TwistWithCovariance();
            TwistWithCovarianceConverter.BinaryReadRecursive(meta, binaryData, obj.twist, baseOff + 608);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Odometry obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForString(obj.child_frame_id, 128), parentOff + 136);
            PoseWithCovarianceConverter.BinaryWriteRecursive(parentOff + 264, writer, allocator, obj.pose);
            TwistWithCovarianceConverter.BinaryWriteRecursive(parentOff + 608, writer, allocator, obj.twist);
        }
    }
}
