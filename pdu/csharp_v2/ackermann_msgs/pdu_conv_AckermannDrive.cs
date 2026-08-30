using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.ackermann_msgs;

namespace Hakoniwa.Pdu.CSharpV2.ackermann_msgs
{
    public static class AckermannDriveConverter
    {
        public static AckermannDrive PduToMsg(byte[] binaryData)
        {
            var obj = new AckermannDrive();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AckermannDrive obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AckermannDrive obj, int baseOff)
        {
            obj.steering_angle = PduRuntime.ReadFloat32(binaryData, baseOff + 0);
            obj.steering_angle_velocity = PduRuntime.ReadFloat32(binaryData, baseOff + 4);
            obj.speed = PduRuntime.ReadFloat32(binaryData, baseOff + 8);
            obj.acceleration = PduRuntime.ReadFloat32(binaryData, baseOff + 12);
            obj.jerk = PduRuntime.ReadFloat32(binaryData, baseOff + 16);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AckermannDrive obj)
        {
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.steering_angle), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.steering_angle_velocity), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.speed), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.acceleration), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.jerk), parentOff + 16);
        }
    }
}
