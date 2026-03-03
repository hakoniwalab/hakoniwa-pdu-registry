using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class HakoDroneCmdLandConverter
    {
        public static HakoDroneCmdLand PduToMsg(byte[] binaryData)
        {
            var obj = new HakoDroneCmdLand();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoDroneCmdLand obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoDroneCmdLand obj, int baseOff)
        {
            obj.header = new HakoDroneCmdHeader();
            HakoDroneCmdHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.height = PduRuntime.ReadFloat64(binaryData, baseOff + 16);
            obj.speed = PduRuntime.ReadFloat64(binaryData, baseOff + 24);
            obj.yaw_deg = PduRuntime.ReadFloat64(binaryData, baseOff + 32);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoDroneCmdLand obj)
        {
            HakoDroneCmdHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.height), parentOff + 16);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.speed), parentOff + 24);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.yaw_deg), parentOff + 32);
        }
    }
}
