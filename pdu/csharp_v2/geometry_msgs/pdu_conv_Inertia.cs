using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.geometry_msgs
{
    public static class InertiaConverter
    {
        public static Inertia PduToMsg(byte[] binaryData)
        {
            var obj = new Inertia();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Inertia obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Inertia obj, int baseOff)
        {
            obj.m = PduRuntime.ReadFloat64(binaryData, baseOff + 0);
            obj.com = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.com, baseOff + 8);
            obj.ixx = PduRuntime.ReadFloat64(binaryData, baseOff + 32);
            obj.ixy = PduRuntime.ReadFloat64(binaryData, baseOff + 40);
            obj.ixz = PduRuntime.ReadFloat64(binaryData, baseOff + 48);
            obj.iyy = PduRuntime.ReadFloat64(binaryData, baseOff + 56);
            obj.iyz = PduRuntime.ReadFloat64(binaryData, baseOff + 64);
            obj.izz = PduRuntime.ReadFloat64(binaryData, baseOff + 72);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Inertia obj)
        {
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.m), parentOff + 0);
            Vector3Converter.BinaryWriteRecursive(parentOff + 8, writer, allocator, obj.com);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.ixx), parentOff + 32);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.ixy), parentOff + 40);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.ixz), parentOff + 48);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.iyy), parentOff + 56);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.iyz), parentOff + 64);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.izz), parentOff + 72);
        }
    }
}
