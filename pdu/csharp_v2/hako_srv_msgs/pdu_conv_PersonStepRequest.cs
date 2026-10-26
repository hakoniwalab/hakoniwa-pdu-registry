using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class PersonStepRequestConverter
    {
        public static PersonStepRequest PduToMsg(byte[] binaryData)
        {
            var obj = new PersonStepRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(PersonStepRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, PersonStepRequest obj, int baseOff)
        {
            obj.step = PduRuntime.ReadUInt64(binaryData, baseOff + 0);
            obj.cmd_vel = new Twist();
            TwistConverter.BinaryReadRecursive(meta, binaryData, obj.cmd_vel, baseOff + 8);
            obj.animation = PduRuntime.ReadString(binaryData, baseOff + 56, 128);
            obj.ride = PduRuntime.ReadString(binaryData, baseOff + 184, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, PersonStepRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.step), parentOff + 0);
            TwistConverter.BinaryWriteRecursive(parentOff + 8, writer, allocator, obj.cmd_vel);
            allocator.Add(PduRuntime.GetBinaryForString(obj.animation, 128), parentOff + 56);
            allocator.Add(PduRuntime.GetBinaryForString(obj.ride, 128), parentOff + 184);
        }
    }
}
