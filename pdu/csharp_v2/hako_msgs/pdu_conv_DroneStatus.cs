using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class DroneStatusConverter
    {
        public static DroneStatus PduToMsg(byte[] binaryData)
        {
            var obj = new DroneStatus();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(DroneStatus obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, DroneStatus obj, int baseOff)
        {
            obj.flight_mode = PduRuntime.ReadInt32(binaryData, baseOff + 0);
            obj.internal_state = PduRuntime.ReadInt32(binaryData, baseOff + 4);
            obj.propeller_wind = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.propeller_wind, baseOff + 8);
            obj.collided_counts = PduRuntime.ReadInt32(binaryData, baseOff + 32);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, DroneStatus obj)
        {
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.flight_mode), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.internal_state), parentOff + 4);
            Vector3Converter.BinaryWriteRecursive(parentOff + 8, writer, allocator, obj.propeller_wind);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.collided_counts), parentOff + 32);
        }
    }
}
