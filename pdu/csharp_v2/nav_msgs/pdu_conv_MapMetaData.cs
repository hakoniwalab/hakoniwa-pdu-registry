using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.nav_msgs;
using Hakoniwa.Pdu.CSharpV2.builtin_interfaces;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.nav_msgs
{
    public static class MapMetaDataConverter
    {
        public static MapMetaData PduToMsg(byte[] binaryData)
        {
            var obj = new MapMetaData();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(MapMetaData obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, MapMetaData obj, int baseOff)
        {
            obj.map_load_time = new Time();
            TimeConverter.BinaryReadRecursive(meta, binaryData, obj.map_load_time, baseOff + 0);
            obj.resolution = PduRuntime.ReadFloat32(binaryData, baseOff + 8);
            obj.width = PduRuntime.ReadUInt32(binaryData, baseOff + 12);
            obj.height = PduRuntime.ReadUInt32(binaryData, baseOff + 16);
            obj.origin = new Pose();
            PoseConverter.BinaryReadRecursive(meta, binaryData, obj.origin, baseOff + 24);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, MapMetaData obj)
        {
            TimeConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.map_load_time);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.resolution), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.width), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.height), parentOff + 16);
            PoseConverter.BinaryWriteRecursive(parentOff + 24, writer, allocator, obj.origin);
        }
    }
}
