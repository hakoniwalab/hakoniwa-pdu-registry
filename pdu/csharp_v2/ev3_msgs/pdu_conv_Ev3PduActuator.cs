using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.ev3_msgs;

namespace Hakoniwa.Pdu.CSharpV2.ev3_msgs
{
    public static class Ev3PduActuatorConverter
    {
        public static Ev3PduActuator PduToMsg(byte[] binaryData)
        {
            var obj = new Ev3PduActuator();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Ev3PduActuator obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Ev3PduActuator obj, int baseOff)
        {
            obj.head = new Ev3PduActuatorHeader();
            Ev3PduActuatorHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.head, baseOff + 0);
            obj.leds = new List<byte>();
            for (var i = 0; i < 1; i++) {
                obj.leds.Add(PduRuntime.ReadUInt8(binaryData, baseOff + 152 + (i * 1)));
            }
            obj.motors = new List<Ev3PduMotor>();
            for (var i = 0; i < 3; i++) {
                var tmp = new Ev3PduMotor();
                Ev3PduMotorConverter.BinaryReadRecursive(meta, binaryData, tmp, baseOff + 156 + (i * 12));
                obj.motors.Add(tmp);
            }
            obj.gyro_reset = PduRuntime.ReadUInt32(binaryData, baseOff + 192);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Ev3PduActuator obj)
        {
            Ev3PduActuatorHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.head);
            for (var i = 0; i < obj.leds.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForUInt8(obj.leds[i]), parentOff + 152 + (i * 1));
            }
            for (var i = 0; i < obj.motors.Count; i++) {
                Ev3PduMotorConverter.BinaryWriteRecursive(parentOff + 156 + (i * 12), writer, allocator, obj.motors[i]);
            }
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.gyro_reset), parentOff + 192);
        }
    }
}
