using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class DisturbanceAtmConverter
    {
        public static DisturbanceAtm PduToMsg(byte[] binaryData)
        {
            var obj = new DisturbanceAtm();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(DisturbanceAtm obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, DisturbanceAtm obj, int baseOff)
        {
            obj.sea_level_atm = PduRuntime.ReadFloat64(binaryData, baseOff + 0);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, DisturbanceAtm obj)
        {
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.sea_level_atm), parentOff + 0);
        }
    }
}
