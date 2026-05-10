using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class JoyFeedbackConverter
    {
        public static JoyFeedback PduToMsg(byte[] binaryData)
        {
            var obj = new JoyFeedback();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(JoyFeedback obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, JoyFeedback obj, int baseOff)
        {
            obj.type = PduRuntime.ReadUInt8(binaryData, baseOff + 0);
            obj.id = PduRuntime.ReadUInt8(binaryData, baseOff + 1);
            obj.intensity = PduRuntime.ReadFloat32(binaryData, baseOff + 4);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, JoyFeedback obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.type), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.id), parentOff + 1);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.intensity), parentOff + 4);
        }
    }
}
