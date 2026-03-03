using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_mavlink_msgs
{
    public static class HakoHilStateQuaternionConverter
    {
        public static HakoHilStateQuaternion PduToMsg(byte[] binaryData)
        {
            var obj = new HakoHilStateQuaternion();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoHilStateQuaternion obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoHilStateQuaternion obj, int baseOff)
        {
            obj.time_usec = PduRuntime.ReadUInt64(binaryData, baseOff + 0);
            obj.attitude_quaternion = new List<float>();
            for (var i = 0; i < 4; i++) {
                obj.attitude_quaternion.Add(PduRuntime.ReadFloat32(binaryData, baseOff + 8 + (i * 4)));
            }
            obj.rollspeed = PduRuntime.ReadFloat32(binaryData, baseOff + 24);
            obj.pitchspeed = PduRuntime.ReadFloat32(binaryData, baseOff + 28);
            obj.yawspeed = PduRuntime.ReadFloat32(binaryData, baseOff + 32);
            obj.lat = PduRuntime.ReadInt32(binaryData, baseOff + 36);
            obj.lon = PduRuntime.ReadInt32(binaryData, baseOff + 40);
            obj.alt = PduRuntime.ReadInt32(binaryData, baseOff + 44);
            obj.vx = PduRuntime.ReadInt16(binaryData, baseOff + 48);
            obj.vy = PduRuntime.ReadInt16(binaryData, baseOff + 50);
            obj.vz = PduRuntime.ReadInt16(binaryData, baseOff + 52);
            obj.ind_airspeed = PduRuntime.ReadUInt16(binaryData, baseOff + 54);
            obj.true_airspeed = PduRuntime.ReadUInt16(binaryData, baseOff + 56);
            obj.xacc = PduRuntime.ReadInt16(binaryData, baseOff + 58);
            obj.yacc = PduRuntime.ReadInt16(binaryData, baseOff + 60);
            obj.zacc = PduRuntime.ReadInt16(binaryData, baseOff + 62);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoHilStateQuaternion obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.time_usec), parentOff + 0);
            for (var i = 0; i < obj.attitude_quaternion.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForFloat32(obj.attitude_quaternion[i]), parentOff + 8 + (i * 4));
            }
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.rollspeed), parentOff + 24);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.pitchspeed), parentOff + 28);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.yawspeed), parentOff + 32);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.lat), parentOff + 36);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.lon), parentOff + 40);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.alt), parentOff + 44);
            allocator.Add(PduRuntime.GetBinaryForInt16(obj.vx), parentOff + 48);
            allocator.Add(PduRuntime.GetBinaryForInt16(obj.vy), parentOff + 50);
            allocator.Add(PduRuntime.GetBinaryForInt16(obj.vz), parentOff + 52);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.ind_airspeed), parentOff + 54);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.true_airspeed), parentOff + 56);
            allocator.Add(PduRuntime.GetBinaryForInt16(obj.xacc), parentOff + 58);
            allocator.Add(PduRuntime.GetBinaryForInt16(obj.yacc), parentOff + 60);
            allocator.Add(PduRuntime.GetBinaryForInt16(obj.zacc), parentOff + 62);
        }
    }
}
