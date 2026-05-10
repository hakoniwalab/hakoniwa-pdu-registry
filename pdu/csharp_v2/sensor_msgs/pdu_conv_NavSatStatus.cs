using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class NavSatStatusConverter
    {
        public static NavSatStatus PduToMsg(byte[] binaryData)
        {
            var obj = new NavSatStatus();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(NavSatStatus obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, NavSatStatus obj, int baseOff)
        {
            obj.status = PduRuntime.ReadInt8(binaryData, baseOff + 0);
            obj.service = PduRuntime.ReadUInt16(binaryData, baseOff + 2);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, NavSatStatus obj)
        {
            allocator.Add(PduRuntime.GetBinaryForInt8(obj.status), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.service), parentOff + 2);
        }
    }
}
