using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class WrenchConverter
    {
        public static Wrench PduToMsg(byte[] binaryData)
        {
            var obj = new Wrench();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Wrench obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Wrench obj, int baseOff)
        {
            obj.force = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.force, baseOff + 0);
            obj.torque = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.torque, baseOff + 24);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Wrench obj)
        {
            Vector3Converter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.force);
            Vector3Converter.BinaryWriteRecursive(parentOff + 24, writer, allocator, obj.torque);
        }
    }
}
