using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class MetaPduConverter
    {
        public static MetaPdu PduToMsg(byte[] binaryData)
        {
            var obj = new MetaPdu();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(MetaPdu obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, MetaPdu obj, int baseOff)
        {
            obj.total_len = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.magicno = PduRuntime.ReadUInt32(binaryData, baseOff + 4);
            obj.version = PduRuntime.ReadUInt16(binaryData, baseOff + 8);
            obj.flags = PduRuntime.ReadUInt16(binaryData, baseOff + 10);
            obj.meta_request_type = PduRuntime.ReadUInt32(binaryData, baseOff + 12);
            obj.hako_time_us = PduRuntime.ReadUInt64(binaryData, baseOff + 16);
            obj.asset_time_us = PduRuntime.ReadUInt64(binaryData, baseOff + 24);
            obj.real_time_us = PduRuntime.ReadUInt64(binaryData, baseOff + 32);
            obj.robot_name = PduRuntime.ReadString(binaryData, baseOff + 40, 128);
            obj.channel_id = PduRuntime.ReadInt32(binaryData, baseOff + 168);
            obj.body_len = PduRuntime.ReadUInt32(binaryData, baseOff + 172);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, MetaPdu obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.total_len), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.magicno), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.version), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForUInt16(obj.flags), parentOff + 10);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.meta_request_type), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.hako_time_us), parentOff + 16);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.asset_time_us), parentOff + 24);
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.real_time_us), parentOff + 32);
            allocator.Add(PduRuntime.GetBinaryForString(obj.robot_name, 128), parentOff + 40);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.channel_id), parentOff + 168);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.body_len), parentOff + 172);
        }
    }
}
