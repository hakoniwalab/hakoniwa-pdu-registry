using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class DisturbanceTemperatureConverter
    {
        public static DisturbanceTemperature PduToMsg(byte[] binaryData)
        {
            var obj = new DisturbanceTemperature();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(DisturbanceTemperature obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, DisturbanceTemperature obj, int baseOff)
        {
            obj.value = PduRuntime.ReadFloat64(binaryData, baseOff + 0);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, DisturbanceTemperature obj)
        {
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.value), parentOff + 0);
        }
    }
}
