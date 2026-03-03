using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class ImuConverter
    {
        public static Imu PduToMsg(byte[] binaryData)
        {
            var obj = new Imu();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Imu obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Imu obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.orientation = new Quaternion();
            QuaternionConverter.BinaryReadRecursive(meta, binaryData, obj.orientation, baseOff + 136);
            obj.orientation_covariance = new List<double>();
            for (var i = 0; i < 9; i++) {
                obj.orientation_covariance.Add(PduRuntime.ReadFloat64(binaryData, baseOff + 168 + (i * 8)));
            }
            obj.angular_velocity = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.angular_velocity, baseOff + 240);
            obj.angular_velocity_covariance = new List<double>();
            for (var i = 0; i < 9; i++) {
                obj.angular_velocity_covariance.Add(PduRuntime.ReadFloat64(binaryData, baseOff + 264 + (i * 8)));
            }
            obj.linear_acceleration = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.linear_acceleration, baseOff + 336);
            obj.linear_acceleration_covariance = new List<double>();
            for (var i = 0; i < 9; i++) {
                obj.linear_acceleration_covariance.Add(PduRuntime.ReadFloat64(binaryData, baseOff + 360 + (i * 8)));
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Imu obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            QuaternionConverter.BinaryWriteRecursive(parentOff + 136, writer, allocator, obj.orientation);
            for (var i = 0; i < obj.orientation_covariance.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForFloat64(obj.orientation_covariance[i]), parentOff + 168 + (i * 8));
            }
            Vector3Converter.BinaryWriteRecursive(parentOff + 240, writer, allocator, obj.angular_velocity);
            for (var i = 0; i < obj.angular_velocity_covariance.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForFloat64(obj.angular_velocity_covariance[i]), parentOff + 264 + (i * 8));
            }
            Vector3Converter.BinaryWriteRecursive(parentOff + 336, writer, allocator, obj.linear_acceleration);
            for (var i = 0; i < obj.linear_acceleration_covariance.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForFloat64(obj.linear_acceleration_covariance[i]), parentOff + 360 + (i * 8));
            }
        }
    }
}
