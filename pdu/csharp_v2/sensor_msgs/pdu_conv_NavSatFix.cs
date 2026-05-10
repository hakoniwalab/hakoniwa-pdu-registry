using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class NavSatFixConverter
    {
        public static NavSatFix PduToMsg(byte[] binaryData)
        {
            var obj = new NavSatFix();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(NavSatFix obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, NavSatFix obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.status = new NavSatStatus();
            NavSatStatusConverter.BinaryReadRecursive(meta, binaryData, obj.status, baseOff + 136);
            obj.latitude = PduRuntime.ReadFloat64(binaryData, baseOff + 144);
            obj.longitude = PduRuntime.ReadFloat64(binaryData, baseOff + 152);
            obj.altitude = PduRuntime.ReadFloat64(binaryData, baseOff + 160);
            obj.position_covariance = new List<double>();
            for (var i = 0; i < 9; i++) {
                obj.position_covariance.Add(PduRuntime.ReadFloat64(binaryData, baseOff + 168 + (i * 8)));
            }
            obj.position_covariance_type = PduRuntime.ReadUInt8(binaryData, baseOff + 240);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, NavSatFix obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            NavSatStatusConverter.BinaryWriteRecursive(parentOff + 136, writer, allocator, obj.status);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.latitude), parentOff + 144);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.longitude), parentOff + 152);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.altitude), parentOff + 160);
            for (var i = 0; i < obj.position_covariance.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForFloat64(obj.position_covariance[i]), parentOff + 168 + (i * 8));
            }
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.position_covariance_type), parentOff + 240);
        }
    }
}
