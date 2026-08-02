using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_action_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_action_msgs
{
    public static class ActionResponseHeaderConverter
    {
        public static ActionResponseHeader PduToMsg(byte[] binaryData)
        {
            var obj = new ActionResponseHeader();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ActionResponseHeader obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ActionResponseHeader obj, int baseOff)
        {
            obj.version = PduRuntime.ReadUInt8(binaryData, baseOff + 0);
            obj.response_kind = PduRuntime.ReadUInt8(binaryData, baseOff + 1);
            obj.status = PduRuntime.ReadUInt8(binaryData, baseOff + 2);
            obj.reserved = PduRuntime.ReadUInt8(binaryData, baseOff + 3);
            obj.goal_id = new List<byte>();
            for (var i = 0; i < 16; i++) {
                obj.goal_id.Add(PduRuntime.ReadUInt8(binaryData, baseOff + 4 + (i * 1)));
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ActionResponseHeader obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.version), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.response_kind), parentOff + 1);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.status), parentOff + 2);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.reserved), parentOff + 3);
            for (var i = 0; i < obj.goal_id.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForUInt8(obj.goal_id[i]), parentOff + 4 + (i * 1));
            }
        }
    }
}
