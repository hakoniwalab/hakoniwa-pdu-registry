using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class LightStateConverter
    {
        public static LightState PduToMsg(byte[] binaryData)
        {
            var obj = new LightState();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(LightState obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, LightState obj, int baseOff)
        {
            obj.source = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.mode = PduRuntime.ReadUInt8(binaryData, baseOff + 128);
            obj.luminous_intensity_scale = PduRuntime.ReadFloat64(binaryData, baseOff + 136);
            obj.is_lit = PduRuntime.ReadBool(binaryData, baseOff + 144);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, LightState obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.source, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.mode), parentOff + 128);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.luminous_intensity_scale), parentOff + 136);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.is_lit), parentOff + 144);
        }
    }
}
