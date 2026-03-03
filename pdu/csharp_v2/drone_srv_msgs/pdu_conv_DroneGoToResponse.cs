using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.drone_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public static class DroneGoToResponseConverter
    {
        public static DroneGoToResponse PduToMsg(byte[] binaryData)
        {
            var obj = new DroneGoToResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(DroneGoToResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, DroneGoToResponse obj, int baseOff)
        {
            obj.ok = PduRuntime.ReadBool(binaryData, baseOff + 0);
            obj.message = PduRuntime.ReadString(binaryData, baseOff + 4, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, DroneGoToResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForBool(obj.ok), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForString(obj.message, 128), parentOff + 4);
        }
    }
}
