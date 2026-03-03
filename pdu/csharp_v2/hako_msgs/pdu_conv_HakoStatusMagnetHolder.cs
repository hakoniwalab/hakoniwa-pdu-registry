using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class HakoStatusMagnetHolderConverter
    {
        public static HakoStatusMagnetHolder PduToMsg(byte[] binaryData)
        {
            var obj = new HakoStatusMagnetHolder();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoStatusMagnetHolder obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoStatusMagnetHolder obj, int baseOff)
        {
            obj.magnet_on = PduRuntime.ReadBool(binaryData, baseOff + 0);
            obj.contact_on = PduRuntime.ReadBool(binaryData, baseOff + 4);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoStatusMagnetHolder obj)
        {
            allocator.Add(PduRuntime.GetBinaryForBool(obj.magnet_on), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.contact_on), parentOff + 4);
        }
    }
}
