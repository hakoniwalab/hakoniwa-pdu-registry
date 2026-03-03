using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class CollisionConverter
    {
        public static Collision PduToMsg(byte[] binaryData)
        {
            var obj = new Collision();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Collision obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Collision obj, int baseOff)
        {
            obj.collision = PduRuntime.ReadBool(binaryData, baseOff + 0);
            obj.contact_num = PduRuntime.ReadUInt32(binaryData, baseOff + 4);
            obj.relative_velocity = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.relative_velocity, baseOff + 8);
            obj.contact_position = new List<Point>();
            for (var i = 0; i < 10; i++) {
                var tmp = new Point();
                PointConverter.BinaryReadRecursive(meta, binaryData, tmp, baseOff + 32 + (i * 24));
                obj.contact_position.Add(tmp);
            }
            obj.restitution_coefficient = PduRuntime.ReadFloat64(binaryData, baseOff + 272);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Collision obj)
        {
            allocator.Add(PduRuntime.GetBinaryForBool(obj.collision), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.contact_num), parentOff + 4);
            Vector3Converter.BinaryWriteRecursive(parentOff + 8, writer, allocator, obj.relative_velocity);
            for (var i = 0; i < obj.contact_position.Count; i++) {
                PointConverter.BinaryWriteRecursive(parentOff + 32 + (i * 24), writer, allocator, obj.contact_position[i]);
            }
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.restitution_coefficient), parentOff + 272);
        }
    }
}
