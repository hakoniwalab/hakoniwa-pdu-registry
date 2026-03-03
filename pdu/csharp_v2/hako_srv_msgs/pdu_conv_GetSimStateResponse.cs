using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class GetSimStateResponseConverter
    {
        public static GetSimStateResponse PduToMsg(byte[] binaryData)
        {
            var obj = new GetSimStateResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(GetSimStateResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, GetSimStateResponse obj, int baseOff)
        {
            obj.sim_state = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.master_time = PduRuntime.ReadInt64(binaryData, baseOff + 8);
            obj.is_pdu_created = PduRuntime.ReadBool(binaryData, baseOff + 16);
            obj.is_simulation_mode = PduRuntime.ReadBool(binaryData, baseOff + 20);
            obj.is_pdu_sync_mode = PduRuntime.ReadBool(binaryData, baseOff + 24);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, GetSimStateResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.sim_state), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForInt64(obj.master_time), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.is_pdu_created), parentOff + 16);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.is_simulation_mode), parentOff + 20);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.is_pdu_sync_mode), parentOff + 24);
        }
    }
}
