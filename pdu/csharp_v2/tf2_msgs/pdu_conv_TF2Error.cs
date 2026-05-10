using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.tf2_msgs;

namespace Hakoniwa.Pdu.CSharpV2.tf2_msgs
{
    public static class TF2ErrorConverter
    {
        public static TF2Error PduToMsg(byte[] binaryData)
        {
            var obj = new TF2Error();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(TF2Error obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, TF2Error obj, int baseOff)
        {
            obj.error = PduRuntime.ReadUInt8(binaryData, baseOff + 0);
            obj.error_string = PduRuntime.ReadString(binaryData, baseOff + 1, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, TF2Error obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.error), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForString(obj.error_string, 128), parentOff + 1);
        }
    }
}
