using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.drone_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public static class MagnetGrabResponseConverter
    {
        public static MagnetGrabResponse PduToMsg(byte[] binaryData)
        {
            var obj = new MagnetGrabResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(MagnetGrabResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, MagnetGrabResponse obj, int baseOff)
        {
            obj.ok = PduRuntime.ReadBool(binaryData, baseOff + 0);
            obj.magnet_on = PduRuntime.ReadBool(binaryData, baseOff + 4);
            obj.contact_on = PduRuntime.ReadBool(binaryData, baseOff + 8);
            obj.message = PduRuntime.ReadString(binaryData, baseOff + 12, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, MagnetGrabResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForBool(obj.ok), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.magnet_on), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.contact_on), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForString(obj.message, 128), parentOff + 12);
        }
    }
}
