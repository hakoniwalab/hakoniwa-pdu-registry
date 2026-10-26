using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class SetLightRequestConverter
    {
        public static SetLightRequest PduToMsg(byte[] binaryData)
        {
            var obj = new SetLightRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(SetLightRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, SetLightRequest obj, int baseOff)
        {
            obj.source = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.mode = PduRuntime.ReadUInt8(binaryData, baseOff + 128);
            obj.luminous_intensity_scale = PduRuntime.ReadFloat64(binaryData, baseOff + 136);
            obj.flashing_on_s = PduRuntime.ReadFloat64(binaryData, baseOff + 144);
            obj.flashing_off_s = PduRuntime.ReadFloat64(binaryData, baseOff + 152);
            obj.transition_s = PduRuntime.ReadFloat64(binaryData, baseOff + 160);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, SetLightRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.source, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.mode), parentOff + 128);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.luminous_intensity_scale), parentOff + 136);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.flashing_on_s), parentOff + 144);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.flashing_off_s), parentOff + 152);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.transition_s), parentOff + 160);
        }
    }
}
