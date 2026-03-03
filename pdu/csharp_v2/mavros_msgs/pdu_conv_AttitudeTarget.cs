using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.mavros_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.mavros_msgs
{
    public static class AttitudeTargetConverter
    {
        public static AttitudeTarget PduToMsg(byte[] binaryData)
        {
            var obj = new AttitudeTarget();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(AttitudeTarget obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, AttitudeTarget obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.type_mask = PduRuntime.ReadUInt8(binaryData, baseOff + 136);
            obj.orientation = new Quaternion();
            QuaternionConverter.BinaryReadRecursive(meta, binaryData, obj.orientation, baseOff + 144);
            obj.body_rate = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.body_rate, baseOff + 176);
            obj.thrust = PduRuntime.ReadFloat32(binaryData, baseOff + 200);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, AttitudeTarget obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.type_mask), parentOff + 136);
            QuaternionConverter.BinaryWriteRecursive(parentOff + 144, writer, allocator, obj.orientation);
            Vector3Converter.BinaryWriteRecursive(parentOff + 176, writer, allocator, obj.body_rate);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.thrust), parentOff + 200);
        }
    }
}
