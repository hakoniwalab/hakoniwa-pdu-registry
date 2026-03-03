using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class HakoCmdMagnetHolderConverter
    {
        public static HakoCmdMagnetHolder PduToMsg(byte[] binaryData)
        {
            var obj = new HakoCmdMagnetHolder();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoCmdMagnetHolder obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoCmdMagnetHolder obj, int baseOff)
        {
            obj.header = new HakoCmdHeader();
            HakoCmdHeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.magnet_on = PduRuntime.ReadBool(binaryData, baseOff + 12);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoCmdMagnetHolder obj)
        {
            HakoCmdHeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.magnet_on), parentOff + 12);
        }
    }
}
