using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class ServiceRequestHeaderConverter
    {
        public static ServiceRequestHeader PduToMsg(byte[] binaryData)
        {
            var obj = new ServiceRequestHeader();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ServiceRequestHeader obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ServiceRequestHeader obj, int baseOff)
        {
            obj.request_id = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.service_name = PduRuntime.ReadString(binaryData, baseOff + 4, 128);
            obj.client_name = PduRuntime.ReadString(binaryData, baseOff + 132, 128);
            obj.opcode = PduRuntime.ReadUInt8(binaryData, baseOff + 260);
            obj.status_poll_interval_msec = PduRuntime.ReadInt32(binaryData, baseOff + 264);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ServiceRequestHeader obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.request_id), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForString(obj.service_name, 128), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForString(obj.client_name, 128), parentOff + 132);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.opcode), parentOff + 260);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.status_poll_interval_msec), parentOff + 264);
        }
    }
}
