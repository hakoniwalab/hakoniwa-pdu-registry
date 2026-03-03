using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.drone_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public static class DroneSetReadyRequestConverter
    {
        public static DroneSetReadyRequest PduToMsg(byte[] binaryData)
        {
            var obj = new DroneSetReadyRequest();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(DroneSetReadyRequest obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, DroneSetReadyRequest obj, int baseOff)
        {
            obj.drone_name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, DroneSetReadyRequest obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.drone_name, 128), parentOff + 0);
        }
    }
}
