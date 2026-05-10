using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class MagneticFieldConverter
    {
        public static MagneticField PduToMsg(byte[] binaryData)
        {
            var obj = new MagneticField();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(MagneticField obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, MagneticField obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.magnetic_field = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.magnetic_field, baseOff + 136);
            obj.magnetic_field_covariance = new List<double>();
            for (var i = 0; i < 9; i++) {
                obj.magnetic_field_covariance.Add(PduRuntime.ReadFloat64(binaryData, baseOff + 160 + (i * 8)));
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, MagneticField obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            Vector3Converter.BinaryWriteRecursive(parentOff + 136, writer, allocator, obj.magnetic_field);
            for (var i = 0; i < obj.magnetic_field_covariance.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForFloat64(obj.magnetic_field_covariance[i]), parentOff + 160 + (i * 8));
            }
        }
    }
}
