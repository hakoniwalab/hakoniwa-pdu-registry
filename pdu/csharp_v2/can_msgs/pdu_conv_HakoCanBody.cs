using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.can_msgs;

namespace Hakoniwa.Pdu.CSharpV2.can_msgs
{
    public static class HakoCanBodyConverter
    {
        public static HakoCanBody PduToMsg(byte[] binaryData)
        {
            var obj = new HakoCanBody();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoCanBody obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoCanBody obj, int baseOff)
        {
            obj.data = new List<byte>();
            for (var i = 0; i < 8; i++) {
                obj.data.Add(PduRuntime.ReadUInt8(binaryData, baseOff + 0 + (i * 1)));
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoCanBody obj)
        {
            for (var i = 0; i < obj.data.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForUInt8(obj.data[i]), parentOff + 0 + (i * 1));
            }
        }
    }
}
