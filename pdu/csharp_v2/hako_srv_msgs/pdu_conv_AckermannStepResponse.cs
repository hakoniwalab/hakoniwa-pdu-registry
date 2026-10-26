using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class AckermannStepResponseConverter
    {
        public static AckermannStepResponse PduToMsg(byte[] binaryData)
        {
            var obj = new AckermannStepResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AckermannStepResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AckermannStepResponse obj, int baseOff)
        {
            obj.step = PduRuntime.ReadUInt64(binaryData, baseOff + 0);
            obj.result_code = PduRuntime.ReadUInt32(binaryData, baseOff + 8);
            obj.sim_time_usec = PduRuntime.ReadUInt64(binaryData, baseOff + 16);
            obj.pose = new Transform();
            TransformConverter.BinaryReadRecursive(meta, binaryData, obj.pose, baseOff + 24);
            obj.twist = new Twist();
            TwistConverter.BinaryReadRecursive(meta, binaryData, obj.twist, baseOff + 80);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AckermannStepResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.step), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.result_code), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.sim_time_usec), parentOff + 16);
            TransformConverter.BinaryWriteRecursive(parentOff + 24, writer, allocator, obj.pose);
            TwistConverter.BinaryWriteRecursive(parentOff + 80, writer, allocator, obj.twist);
        }
    }
}
