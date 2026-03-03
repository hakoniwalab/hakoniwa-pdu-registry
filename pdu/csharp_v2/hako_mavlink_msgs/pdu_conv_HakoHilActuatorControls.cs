using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public static class HakoHilActuatorControlsConverter
    {
        public static HakoHilActuatorControls PduToMsg(byte[] binaryData)
        {
            var obj = new HakoHilActuatorControls();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoHilActuatorControls obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoHilActuatorControls obj, int baseOff)
        {
            obj.time_usec = PduRuntime.ReadUInt64(binaryData, baseOff + 0);
            obj.controls = new List<float>();
            for (var i = 0; i < 16; i++) {
                obj.controls.Add(PduRuntime.ReadFloat32(binaryData, baseOff + 8 + (i * 4)));
            }
            obj.mode = PduRuntime.ReadUInt8(binaryData, baseOff + 72);
            obj.flags = PduRuntime.ReadUInt64(binaryData, baseOff + 80);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoHilActuatorControls obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.time_usec), parentOff + 0);
            for (var i = 0; i < obj.controls.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForFloat32(obj.controls[i]), parentOff + 8 + (i * 4));
            }
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.mode), parentOff + 72);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.flags), parentOff + 80);
        }
    }
}
