using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class GetSimStateRequestConverter
    {
        public static GetSimStateRequest PduToMsg(byte[] binaryData)
        {
            var obj = new GetSimStateRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(GetSimStateRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, GetSimStateRequest obj, int baseOff)
        {
            obj.name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, GetSimStateRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.name, 128), parentOff + 0);
        }
    }
}
