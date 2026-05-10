using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class TimeReferenceConverter
    {
        public static TimeReference PduToMsg(byte[] binaryData)
        {
            var obj = new TimeReference();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(TimeReference obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, TimeReference obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.time_ref = new Time();
            TimeConverter.BinaryReadRecursive(meta, binaryData, obj.time_ref, baseOff + 136);
            obj.source = PduRuntime.ReadString(binaryData, baseOff + 144, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, TimeReference obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            TimeConverter.BinaryWriteRecursive(parentOff + 136, writer, allocator, obj.time_ref);
            allocator.Add(PduRuntime.GetBinaryForString(obj.source, 128), parentOff + 144);
        }
    }
}
