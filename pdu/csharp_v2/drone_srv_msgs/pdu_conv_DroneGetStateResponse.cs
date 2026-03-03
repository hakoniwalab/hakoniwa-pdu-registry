using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.drone_srv_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public static class DroneGetStateResponseConverter
    {
        public static DroneGetStateResponse PduToMsg(byte[] binaryData)
        {
            var obj = new DroneGetStateResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(DroneGetStateResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, DroneGetStateResponse obj, int baseOff)
        {
            obj.ok = PduRuntime.ReadBool(binaryData, baseOff + 0);
            obj.is_ready = PduRuntime.ReadBool(binaryData, baseOff + 4);
            obj.current_pose = new Pose();
            PoseConverter.BinaryReadRecursive(meta, binaryData, obj.current_pose, baseOff + 8);
            obj.battery_status = new HakoBatteryStatus();
            HakoBatteryStatusConverter.BinaryReadRecursive(meta, binaryData, obj.battery_status, baseOff + 64);
            obj.mode = PduRuntime.ReadString(binaryData, baseOff + 96, 128);
            obj.message = PduRuntime.ReadString(binaryData, baseOff + 224, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, DroneGetStateResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForBool(obj.ok), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.is_ready), parentOff + 4);
            PoseConverter.BinaryWriteRecursive(parentOff + 8, writer, allocator, obj.current_pose);
            HakoBatteryStatusConverter.BinaryWriteRecursive(parentOff + 64, writer, allocator, obj.battery_status);
            allocator.Add(PduRuntime.GetBinaryForString(obj.mode, 128), parentOff + 96);
            allocator.Add(PduRuntime.GetBinaryForString(obj.message, 128), parentOff + 224);
        }
    }
}
