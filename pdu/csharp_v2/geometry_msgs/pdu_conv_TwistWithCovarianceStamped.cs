using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class TwistWithCovarianceStampedConverter
    {
        public static TwistWithCovarianceStamped PduToMsg(byte[] binaryData)
        {
            var obj = new TwistWithCovarianceStamped();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(TwistWithCovarianceStamped obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, TwistWithCovarianceStamped obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.twist = new TwistWithCovariance();
            TwistWithCovarianceConverter.BinaryReadRecursive(meta, binaryData, obj.twist, baseOff + 136);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, TwistWithCovarianceStamped obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            TwistWithCovarianceConverter.BinaryWriteRecursive(parentOff + 136, writer, allocator, obj.twist);
        }
    }
}
