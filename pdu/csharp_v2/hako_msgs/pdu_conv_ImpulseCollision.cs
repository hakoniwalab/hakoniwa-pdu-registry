using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class ImpulseCollisionConverter
    {
        public static ImpulseCollision PduToMsg(byte[] binaryData)
        {
            var obj = new ImpulseCollision();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ImpulseCollision obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ImpulseCollision obj, int baseOff)
        {
            obj.collision = PduRuntime.ReadBool(binaryData, baseOff + 0);
            obj.is_target_static = PduRuntime.ReadBool(binaryData, baseOff + 4);
            obj.restitution_coefficient = PduRuntime.ReadFloat64(binaryData, baseOff + 8);
            obj.self_contact_vector = new Point();
            PointConverter.BinaryReadRecursive(meta, binaryData, obj.self_contact_vector, baseOff + 16);
            obj.normal = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.normal, baseOff + 40);
            obj.target_contact_vector = new Point();
            PointConverter.BinaryReadRecursive(meta, binaryData, obj.target_contact_vector, baseOff + 64);
            obj.target_velocity = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.target_velocity, baseOff + 88);
            obj.target_angular_velocity = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.target_angular_velocity, baseOff + 112);
            obj.target_euler = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.target_euler, baseOff + 136);
            obj.target_inertia = new Vector3();
            Vector3Converter.BinaryReadRecursive(meta, binaryData, obj.target_inertia, baseOff + 160);
            obj.target_mass = PduRuntime.ReadFloat64(binaryData, baseOff + 184);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ImpulseCollision obj)
        {
            allocator.Add(PduRuntime.GetBinaryForBool(obj.collision), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.is_target_static), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.restitution_coefficient), parentOff + 8);
            PointConverter.BinaryWriteRecursive(parentOff + 16, writer, allocator, obj.self_contact_vector);
            Vector3Converter.BinaryWriteRecursive(parentOff + 40, writer, allocator, obj.normal);
            PointConverter.BinaryWriteRecursive(parentOff + 64, writer, allocator, obj.target_contact_vector);
            Vector3Converter.BinaryWriteRecursive(parentOff + 88, writer, allocator, obj.target_velocity);
            Vector3Converter.BinaryWriteRecursive(parentOff + 112, writer, allocator, obj.target_angular_velocity);
            Vector3Converter.BinaryWriteRecursive(parentOff + 136, writer, allocator, obj.target_euler);
            Vector3Converter.BinaryWriteRecursive(parentOff + 160, writer, allocator, obj.target_inertia);
            allocator.Add(PduRuntime.GetBinaryForFloat64(obj.target_mass), parentOff + 184);
        }
    }
}
