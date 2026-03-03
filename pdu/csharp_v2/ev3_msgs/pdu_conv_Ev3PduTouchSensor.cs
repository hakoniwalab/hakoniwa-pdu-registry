using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.ev3_msgs;

namespace Hakoniwa.Pdu.CSharpV2.ev3_msgs
{
    public static class Ev3PduTouchSensorConverter
    {
        public static Ev3PduTouchSensor PduToMsg(byte[] binaryData)
        {
            var obj = new Ev3PduTouchSensor();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Ev3PduTouchSensor obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Ev3PduTouchSensor obj, int baseOff)
        {
            obj.value = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Ev3PduTouchSensor obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.value), parentOff + 0);
        }
    }
}
