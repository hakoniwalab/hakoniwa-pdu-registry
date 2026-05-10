using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class AccelConverter
    {
        public static Accel PduToMsg(byte[] binaryData)
        {
            var obj = new Accel();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Accel obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Accel obj, int baseOff)
        {
            obj.linear = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.linear, baseOff + 0);
            obj.angular = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.angular, baseOff + 24);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Accel obj)
        {
            Vector3Converter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.linear);
            Vector3Converter.BinaryWriteRecursive(parentOff + 24, writer, allocator, obj.angular);
        }
    }
}
