using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;
using Hakoniwa.Pdu.CSharpV2.ackermann_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class AckermannStepRequestConverter
    {
        public static AckermannStepRequest PduToMsg(byte[] binaryData)
        {
            var obj = new AckermannStepRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AckermannStepRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AckermannStepRequest obj, int baseOff)
        {
            obj.step = PduRuntime.ReadUInt64(binaryData, baseOff + 0);
            obj.drive = new AckermannDrive();
            AckermannDriveConverter.BinaryReadRecursive(meta, binaryData, obj.drive, baseOff + 8);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AckermannStepRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.step), parentOff + 0);
            AckermannDriveConverter.BinaryWriteRecursive(parentOff + 8, writer, allocator, obj.drive);
        }
    }
}
