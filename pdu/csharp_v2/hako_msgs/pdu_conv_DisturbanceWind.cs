using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class DisturbanceWindConverter
    {
        public static DisturbanceWind PduToMsg(byte[] binaryData)
        {
            var obj = new DisturbanceWind();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(DisturbanceWind obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, DisturbanceWind obj, int baseOff)
        {
            obj.value = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.value, baseOff + 0);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, DisturbanceWind obj)
        {
            Vector3Converter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.value);
        }
    }
}
