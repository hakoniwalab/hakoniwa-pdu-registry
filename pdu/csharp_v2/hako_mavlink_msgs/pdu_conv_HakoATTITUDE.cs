using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public static class HakoATTITUDEConverter
    {
        public static HakoATTITUDE PduToMsg(byte[] binaryData)
        {
            var obj = new HakoATTITUDE();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoATTITUDE obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoATTITUDE obj, int baseOff)
        {
            obj.time_boot_ms = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.roll = PduRuntime.ReadFloat32(binaryData, baseOff + 4);
            obj.pitch = PduRuntime.ReadFloat32(binaryData, baseOff + 8);
            obj.yaw = PduRuntime.ReadFloat32(binaryData, baseOff + 12);
            obj.rollspeed = PduRuntime.ReadFloat32(binaryData, baseOff + 16);
            obj.pitchspeed = PduRuntime.ReadFloat32(binaryData, baseOff + 20);
            obj.yawspeed = PduRuntime.ReadFloat32(binaryData, baseOff + 24);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoATTITUDE obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.time_boot_ms), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.roll), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.pitch), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.yaw), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.rollspeed), parentOff + 16);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.pitchspeed), parentOff + 20);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.yawspeed), parentOff + 24);
        }
    }
}
