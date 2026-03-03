using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.can_msgs;

namespace Hakoniwa.Pdu.CSharpV2.can_msgs
{
    public static class HakoCanHeadConverter
    {
        public static HakoCanHead PduToMsg(byte[] binaryData)
        {
            var obj = new HakoCanHead();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoCanHead obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoCanHead obj, int baseOff)
        {
            obj.channel = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.ide = PduRuntime.ReadUInt32(binaryData, baseOff + 4);
            obj.rtr = PduRuntime.ReadUInt32(binaryData, baseOff + 8);
            obj.dlc = PduRuntime.ReadUInt32(binaryData, baseOff + 12);
            obj.canid = PduRuntime.ReadUInt32(binaryData, baseOff + 16);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoCanHead obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.channel), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.ide), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.rtr), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.dlc), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.canid), parentOff + 16);
        }
    }
}
