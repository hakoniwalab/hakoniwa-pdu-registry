using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class PoseWithCovarianceConverter
    {
        public static PoseWithCovariance PduToMsg(byte[] binaryData)
        {
            var obj = new PoseWithCovariance();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(PoseWithCovariance obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, PoseWithCovariance obj, int baseOff)
        {
            obj.pose = new Pose();
            PoseConverter.BinaryReadRecursive(meta, binaryData, obj.pose, baseOff + 0);
            obj.covariance = new List<double>();
            for (var i = 0; i < 36; i++) {
                obj.covariance.Add(PduRuntime.ReadFloat64(binaryData, baseOff + 56 + (i * 8)));
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, PoseWithCovariance obj)
        {
            PoseConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.pose);
            for (var i = 0; i < obj.covariance.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForFloat64(obj.covariance[i]), parentOff + 56 + (i * 8));
            }
        }
    }
}
