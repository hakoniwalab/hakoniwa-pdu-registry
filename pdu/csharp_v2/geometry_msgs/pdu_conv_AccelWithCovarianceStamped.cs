using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class AccelWithCovarianceStampedConverter
    {
        public static AccelWithCovarianceStamped PduToMsg(byte[] binaryData)
        {
            var obj = new AccelWithCovarianceStamped();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AccelWithCovarianceStamped obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AccelWithCovarianceStamped obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.accel = new AccelWithCovariance();
            AccelWithCovarianceConverter.BinaryReadRecursive(meta, binaryData, obj.accel, baseOff + 136);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AccelWithCovarianceStamped obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            AccelWithCovarianceConverter.BinaryWriteRecursive(parentOff + 136, writer, allocator, obj.accel);
        }
    }
}
