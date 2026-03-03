using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public static class HakoHeartbeatConverter
    {
        public static HakoHeartbeat PduToMsg(byte[] binaryData)
        {
            var obj = new HakoHeartbeat();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoHeartbeat obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoHeartbeat obj, int baseOff)
        {
            obj.type = PduRuntime.ReadUInt8(binaryData, baseOff + 0);
            obj.autopilot = PduRuntime.ReadUInt8(binaryData, baseOff + 1);
            obj.base_mode = PduRuntime.ReadUInt8(binaryData, baseOff + 2);
            obj.custom_mode = PduRuntime.ReadUInt32(binaryData, baseOff + 4);
            obj.system_status = PduRuntime.ReadUInt8(binaryData, baseOff + 8);
            obj.mavlink_version = PduRuntime.ReadUInt8(binaryData, baseOff + 9);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoHeartbeat obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.type), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.autopilot), parentOff + 1);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.base_mode), parentOff + 2);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.custom_mode), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.system_status), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.mavlink_version), parentOff + 9);
        }
    }
}
