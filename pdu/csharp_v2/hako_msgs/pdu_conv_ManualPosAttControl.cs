using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class ManualPosAttControlConverter
    {
        public static ManualPosAttControl PduToMsg(byte[] binaryData)
        {
            var obj = new ManualPosAttControl();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ManualPosAttControl obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ManualPosAttControl obj, int baseOff)
        {
            obj.do_operation = PduRuntime.ReadBool(binaryData, baseOff + 0);
            obj.posatt = new Twist();
            TwistConverter.BinaryReadRecursive(meta, binaryData, obj.posatt, baseOff + 8);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ManualPosAttControl obj)
        {
            allocator.Add(PduRuntime.GetBinaryForBool(obj.do_operation), parentOff + 0);
            TwistConverter.BinaryWriteRecursive(parentOff + 8, writer, allocator, obj.posatt);
        }
    }
}
