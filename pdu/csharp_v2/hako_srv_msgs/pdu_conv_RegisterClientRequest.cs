using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class RegisterClientRequestConverter
    {
        public static RegisterClientRequest PduToMsg(byte[] binaryData)
        {
            var obj = new RegisterClientRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(RegisterClientRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, RegisterClientRequest obj, int baseOff)
        {
            obj.dummy = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, RegisterClientRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.dummy), parentOff + 0);
        }
    }
}
