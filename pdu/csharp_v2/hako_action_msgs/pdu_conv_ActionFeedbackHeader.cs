using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_action_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_action_msgs
{
    public static class ActionFeedbackHeaderConverter
    {
        public static ActionFeedbackHeader PduToMsg(byte[] binaryData)
        {
            var obj = new ActionFeedbackHeader();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ActionFeedbackHeader obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ActionFeedbackHeader obj, int baseOff)
        {
            obj.version = PduRuntime.ReadUInt8(binaryData, baseOff + 0);
            obj.reserved = new List<byte>();
            for (var i = 0; i < 3; i++) {
                obj.reserved.Add(PduRuntime.ReadUInt8(binaryData, baseOff + 1 + (i * 1)));
            }
            obj.goal_id = new List<byte>();
            for (var i = 0; i < 16; i++) {
                obj.goal_id.Add(PduRuntime.ReadUInt8(binaryData, baseOff + 4 + (i * 1)));
            }
            obj.sequence_no = PduRuntime.ReadUInt32(binaryData, baseOff + 20);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ActionFeedbackHeader obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.version), parentOff + 0);
            for (var i = 0; i < obj.reserved.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForUInt8(obj.reserved[i]), parentOff + 1 + (i * 1));
            }
            for (var i = 0; i < obj.goal_id.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForUInt8(obj.goal_id[i]), parentOff + 4 + (i * 1));
            }
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.sequence_no), parentOff + 20);
        }
    }
}
