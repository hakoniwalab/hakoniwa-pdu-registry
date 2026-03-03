using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class ServiceResponseHeaderConverter
    {
        public static ServiceResponseHeader PduToMsg(byte[] binaryData)
        {
            var obj = new ServiceResponseHeader();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ServiceResponseHeader obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ServiceResponseHeader obj, int baseOff)
        {
            obj.request_id = PduRuntime.ReadUInt32(binaryData, baseOff + 0);
            obj.service_name = PduRuntime.ReadString(binaryData, baseOff + 4, 128);
            obj.client_name = PduRuntime.ReadString(binaryData, baseOff + 132, 128);
            obj.status = PduRuntime.ReadUInt8(binaryData, baseOff + 260);
            obj.processing_percentage = PduRuntime.ReadUInt8(binaryData, baseOff + 261);
            obj.result_code = PduRuntime.ReadInt32(binaryData, baseOff + 264);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ServiceResponseHeader obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.request_id), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForString(obj.service_name, 128), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForString(obj.client_name, 128), parentOff + 132);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.status), parentOff + 260);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.processing_percentage), parentOff + 261);
            allocator.Add(PduRuntime.GetBinaryForInt32(obj.result_code), parentOff + 264);
        }
    }
}
