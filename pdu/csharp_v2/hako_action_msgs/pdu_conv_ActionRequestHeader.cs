using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_action_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_action_msgs
{
    public static class ActionRequestHeaderConverter
    {
        public static ActionRequestHeader PduToMsg(byte[] binaryData)
        {
            var obj = new ActionRequestHeader();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ActionRequestHeader obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ActionRequestHeader obj, int baseOff)
        {
            obj.version = PduRuntime.ReadUInt8(binaryData, baseOff + 0);
            obj.request_kind = PduRuntime.ReadUInt8(binaryData, baseOff + 1);
            obj.reserved = new List<byte>();
            for (var i = 0; i < 2; i++) {
                obj.reserved.Add(PduRuntime.ReadUInt8(binaryData, baseOff + 2 + (i * 1)));
            }
            obj.goal_id = new List<byte>();
            for (var i = 0; i < 16; i++) {
                obj.goal_id.Add(PduRuntime.ReadUInt8(binaryData, baseOff + 4 + (i * 1)));
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ActionRequestHeader obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.version), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.request_kind), parentOff + 1);
            for (var i = 0; i < obj.reserved.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForUInt8(obj.reserved[i]), parentOff + 2 + (i * 1));
            }
            for (var i = 0; i < obj.goal_id.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForUInt8(obj.goal_id[i]), parentOff + 4 + (i * 1));
            }
        }
    }
}
