using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.ev3_msgs;

namespace Hakoniwa.Pdu.CSharpV2.ev3_msgs
{
    public static class Ev3PduColorSensorConverter
    {
        public static Ev3PduColorSensor PduToMsg(byte[] binaryData)
        {
            var obj = new Ev3PduColorSensor();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Ev3PduColorSensor obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Ev3PduColorSensor obj, int baseOff)
        {
            obj.color = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.reflect = PduRuntime.ReadUInt32(binaryData, baseOff + 4);
            obj.rgb_r = PduRuntime.ReadUInt32(binaryData, baseOff + 8);
            obj.rgb_g = PduRuntime.ReadUInt32(binaryData, baseOff + 12);
            obj.rgb_b = PduRuntime.ReadUInt32(binaryData, baseOff + 16);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Ev3PduColorSensor obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.color), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.reflect), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.rgb_r), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.rgb_g), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.rgb_b), parentOff + 16);
        }
    }
}
