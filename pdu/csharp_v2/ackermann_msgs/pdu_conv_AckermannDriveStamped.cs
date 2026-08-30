using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.ackermann_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.ackermann_msgs
{
    public static class AckermannDriveStampedConverter
    {
        public static AckermannDriveStamped PduToMsg(byte[] binaryData)
        {
            var obj = new AckermannDriveStamped();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AckermannDriveStamped obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AckermannDriveStamped obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.drive = new AckermannDrive();
            AckermannDriveConverter.BinaryReadRecursive(meta, binaryData, obj.drive, baseOff + 136);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AckermannDriveStamped obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            AckermannDriveConverter.BinaryWriteRecursive(parentOff + 136, writer, allocator, obj.drive);
        }
    }
}
