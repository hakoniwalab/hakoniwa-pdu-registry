using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.mavros_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.mavros_msgs
{
    public static class GlobalPositionTargetConverter
    {
        public static GlobalPositionTarget PduToMsg(byte[] binaryData)
        {
            var obj = new GlobalPositionTarget();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(GlobalPositionTarget obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, GlobalPositionTarget obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.coordinate_frame = PduRuntime.ReadUInt8(binaryData, baseOff + 136);
            obj.type_mask = PduRuntime.ReadUInt16(binaryData, baseOff + 138);
            obj.latitude = PduRuntime.ReadFloat64(binaryData, baseOff + 144);
            obj.longitude = PduRuntime.ReadFloat64(binaryData, baseOff + 152);
            obj.altitude = PduRuntime.ReadFloat32(binaryData, baseOff + 160);
            obj.velocity = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.velocity, baseOff + 168);
            obj.acceleration_or_force = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.acceleration_or_force, baseOff + 192);
            obj.yaw = PduRuntime.ReadFloat32(binaryData, baseOff + 216);
            obj.yaw_rate = PduRuntime.ReadFloat32(binaryData, baseOff + 220);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, GlobalPositionTarget obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.coordinate_frame), parentOff + 136);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.type_mask), parentOff + 138);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.latitude), parentOff + 144);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.longitude), parentOff + 152);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.altitude), parentOff + 160);
            Vector3Converter.BinaryWriteRecursive(parentOff + 168, writer, allocator, obj.velocity);
            Vector3Converter.BinaryWriteRecursive(parentOff + 192, writer, allocator, obj.acceleration_or_force);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.yaw), parentOff + 216);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.yaw_rate), parentOff + 220);
        }
    }
}
