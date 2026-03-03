using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.ev3_msgs;

namespace Hakoniwa.Pdu.CSharpV2.ev3_msgs
{
    public static class Ev3PduSensorConverter
    {
        public static Ev3PduSensor PduToMsg(byte[] binaryData)
        {
            var obj = new Ev3PduSensor();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Ev3PduSensor obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Ev3PduSensor obj, int baseOff)
        {
            obj.head = new Ev3PduSensorHeader();
            Ev3PduSensorHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.head, baseOff + 0);
            obj.buttons = new List<byte>();
            for (var i = 0; i < 1; i++) {
                obj.buttons.Add(PduRuntime.ReadUInt8(binaryData, baseOff + 152 + (i * 1)));
            }
            obj.color_sensors = new List<Ev3PduColorSensor>();
            for (var i = 0; i < 2; i++) {
                var tmp = new Ev3PduColorSensor();
                Ev3PduColorSensorConverter.BinaryReadRecursive(meta, binaryData, tmp, baseOff + 156 + (i * 20));
                obj.color_sensors.Add(tmp);
            }
            obj.touch_sensors = new List<Ev3PduTouchSensor>();
            for (var i = 0; i < 2; i++) {
                var tmp = new Ev3PduTouchSensor();
                Ev3PduTouchSensorConverter.BinaryReadRecursive(meta, binaryData, tmp, baseOff + 196 + (i * 4));
                obj.touch_sensors.Add(tmp);
            }
            obj.motor_angle = new List<uint>();
            for (var i = 0; i < 3; i++) {
                obj.motor_angle.Add(PduRuntime.ReadUInt32(binaryData, baseOff + 204 + (i * 4)));
            }
            obj.gyro_degree = PduRuntime.ReadInt32(binaryData, baseOff + 216);
            obj.gyro_degree_rate = PduRuntime.ReadInt32(binaryData, baseOff + 220);
            obj.sensor_ultrasonic = PduRuntime.ReadUInt32(binaryData, baseOff + 224);
            obj.gps_lat = PduRuntime.ReadFloat64(binaryData, baseOff + 232);
            obj.gps_lon = PduRuntime.ReadFloat64(binaryData, baseOff + 240);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Ev3PduSensor obj)
        {
            Ev3PduSensorHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.head);
            for (var i = 0; i < obj.buttons.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForUInt8(obj.buttons[i]), parentOff + 152 + (i * 1));
            }
            for (var i = 0; i < obj.color_sensors.Count; i++) {
                Ev3PduColorSensorConverter.BinaryWriteRecursive(parentOff + 156 + (i * 20), writer, allocator, obj.color_sensors[i]);
            }
            for (var i = 0; i < obj.touch_sensors.Count; i++) {
                Ev3PduTouchSensorConverter.BinaryWriteRecursive(parentOff + 196 + (i * 4), writer, allocator, obj.touch_sensors[i]);
            }
            for (var i = 0; i < obj.motor_angle.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForUInt32(obj.motor_angle[i]), parentOff + 204 + (i * 4));
            }
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.gyro_degree), parentOff + 216);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.gyro_degree_rate), parentOff + 220);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.sensor_ultrasonic), parentOff + 224);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.gps_lat), parentOff + 232);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.gps_lon), parentOff + 240);
        }
    }
}
