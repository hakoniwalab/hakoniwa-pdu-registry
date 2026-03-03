using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.drone_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public static class DroneTakeOffRequestConverter
    {
        public static DroneTakeOffRequest PduToMsg(byte[] binaryData)
        {
            var obj = new DroneTakeOffRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(DroneTakeOffRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, DroneTakeOffRequest obj, int baseOff)
        {
            obj.alt_m = PduRuntime.ReadFloat64(binaryData, baseOff + 0);
            obj.drone_name = PduRuntime.ReadString(binaryData, baseOff + 8, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, DroneTakeOffRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.alt_m), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForString(obj.drone_name, 128), parentOff + 8);
        }
    }
}
