using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.ev3_msgs;

namespace Hakoniwa.Pdu.CSharpV2.ev3_msgs
{
    public static class Ev3PduSensorHeaderConverter
    {
        public static Ev3PduSensorHeader PduToMsg(byte[] binaryData)
        {
            var obj = new Ev3PduSensorHeader();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Ev3PduSensorHeader obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Ev3PduSensorHeader obj, int baseOff)
        {
            obj.name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.version = PduRuntime.ReadUInt32(binaryData, baseOff + 128);
            obj.hakoniwa_time = PduRuntime.ReadInt64(binaryData, baseOff + 136);
            obj.ext_off = PduRuntime.ReadUInt32(binaryData, baseOff + 144);
            obj.ext_size = PduRuntime.ReadUInt32(binaryData, baseOff + 148);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Ev3PduSensorHeader obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.name, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.version), parentOff + 128);
            allocator.Add(PduRuntime.GetBinaryForInt64(obj.hakoniwa_time), parentOff + 136);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.ext_off), parentOff + 144);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.ext_size), parentOff + 148);
        }
    }
}
