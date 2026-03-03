using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.drone_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public static class MagnetGrabRequestConverter
    {
        public static MagnetGrabRequest PduToMsg(byte[] binaryData)
        {
            var obj = new MagnetGrabRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(MagnetGrabRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, MagnetGrabRequest obj, int baseOff)
        {
            obj.drone_name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.grab_on = PduRuntime.ReadBool(binaryData, baseOff + 128);
            obj.timeout_sec = PduRuntime.ReadFloat32(binaryData, baseOff + 132);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, MagnetGrabRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.drone_name, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForBool(obj.grab_on), parentOff + 128);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.timeout_sec), parentOff + 132);
        }
    }
}
