using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class HakoCmdHeaderConverter
    {
        public static HakoCmdHeader PduToMsg(byte[] binaryData)
        {
            var obj = new HakoCmdHeader();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(HakoCmdHeader obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, HakoCmdHeader obj, int baseOff)
        {
            obj.request = PduRuntime.ReadBool(binaryData, baseOff + 0);
            obj.result = PduRuntime.ReadBool(binaryData, baseOff + 4);
            obj.result_code = PduRuntime.ReadInt32(binaryData, baseOff + 8);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, HakoCmdHeader obj)
        {
            allocator.Add(PduRuntime.GetBinaryForBool(obj.request), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.result), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.result_code), parentOff + 8);
        }
    }
}
