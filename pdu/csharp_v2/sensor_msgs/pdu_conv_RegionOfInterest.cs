using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class RegionOfInterestConverter
    {
        public static RegionOfInterest PduToMsg(byte[] binaryData)
        {
            var obj = new RegionOfInterest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(RegionOfInterest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, RegionOfInterest obj, int baseOff)
        {
            obj.x_offset = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.y_offset = PduRuntime.ReadUInt32(binaryData, baseOff + 4);
            obj.height = PduRuntime.ReadUInt32(binaryData, baseOff + 8);
            obj.width = PduRuntime.ReadUInt32(binaryData, baseOff + 12);
            obj.do_rectify = PduRuntime.ReadBool(binaryData, baseOff + 16);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, RegionOfInterest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.x_offset), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.y_offset), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.height), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.width), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.do_rectify), parentOff + 16);
        }
    }
}
