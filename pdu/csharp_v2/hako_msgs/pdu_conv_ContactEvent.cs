using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class ContactEventConverter
    {
        public static ContactEvent PduToMsg(byte[] binaryData)
        {
            var obj = new ContactEvent();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ContactEvent obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ContactEvent obj, int baseOff)
        {
            obj.stamp = new Time();
            TimeConverter.BinaryReadRecursive(meta, binaryData, obj.stamp, baseOff + 0);
            obj.self_name = PduRuntime.ReadString(binaryData, baseOff + 8, 128);
            obj.other_name = PduRuntime.ReadString(binaryData, baseOff + 136, 128);
            obj.other_kind = PduRuntime.ReadString(binaryData, baseOff + 264, 128);
            obj.position = new Point();
            PointConverter.BinaryReadRecursive(meta, binaryData, obj.position, baseOff + 392);
            obj.relative_speed = PduRuntime.ReadFloat64(binaryData, baseOff + 416);
            obj.started = PduRuntime.ReadBool(binaryData, baseOff + 424);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ContactEvent obj)
        {
            TimeConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.stamp);
            allocator.Add(PduRuntime.GetBinaryForString(obj.self_name, 128), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForString(obj.other_name, 128), parentOff + 136);
            allocator.Add(PduRuntime.GetBinaryForString(obj.other_kind, 128), parentOff + 264);
            PointConverter.BinaryWriteRecursive(parentOff + 392, writer, allocator, obj.position);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.relative_speed), parentOff + 416);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.started), parentOff + 424);
        }
    }
}
