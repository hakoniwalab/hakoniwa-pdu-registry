using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class AccelWithCovarianceConverter
    {
        public static AccelWithCovariance PduToMsg(byte[] binaryData)
        {
            var obj = new AccelWithCovariance();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AccelWithCovariance obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AccelWithCovariance obj, int baseOff)
        {
            obj.accel = new Accel();
            AccelConverter.BinaryReadRecursive(meta, binaryData, obj.accel, baseOff + 0);
            obj.covariance = new List<double>();
            for (var i = 0; i < 36; i++) {
                obj.covariance.Add(PduRuntime.ReadFloat64(binaryData, baseOff + 48 + (i * 8)));
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AccelWithCovariance obj)
        {
            AccelConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.accel);
            for (var i = 0; i < obj.covariance.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForFloat64(obj.covariance[i]), parentOff + 48 + (i * 8));
            }
        }
    }
}
