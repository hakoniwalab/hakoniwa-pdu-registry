using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.ev3_msgs;

namespace Hakoniwa.Pdu.CSharpV2.ev3_msgs
{
    public static class Ev3PduMotorConverter
    {
        public static Ev3PduMotor PduToMsg(byte[] binaryData)
        {
            var obj = new Ev3PduMotor();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Ev3PduMotor obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Ev3PduMotor obj, int baseOff)
        {
            obj.power = PduRuntime.ReadInt32(binaryData, baseOff + 0);
            obj.stop = PduRuntime.ReadUInt32(binaryData, baseOff + 4);
            obj.reset_angle = PduRuntime.ReadUInt32(binaryData, baseOff + 8);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Ev3PduMotor obj)
        {
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.power), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.stop), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.reset_angle), parentOff + 8);
        }
    }
}
