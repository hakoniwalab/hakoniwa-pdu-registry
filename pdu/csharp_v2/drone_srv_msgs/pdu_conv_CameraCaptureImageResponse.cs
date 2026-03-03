using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.drone_srv_msgs;

namespace Hakoniwa.Pdu.CSharpV2.drone_srv_msgs
{
    public static class CameraCaptureImageResponseConverter
    {
        public static CameraCaptureImageResponse PduToMsg(byte[] binaryData)
        {
            var obj = new CameraCaptureImageResponse();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(CameraCaptureImageResponse obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, CameraCaptureImageResponse obj, int baseOff)
        {
            obj.ok = PduRuntime.ReadBool(binaryData, baseOff + 0);
            obj.data = new List<byte>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 4);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 4 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.data.Add(PduRuntime.ReadUInt8(binaryData, meta.HeapOff + offsetFromHeap + (i * 1)));
                }
            }
            obj.message = PduRuntime.ReadString(binaryData, baseOff + 12, 128);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, CameraCaptureImageResponse obj)
        {
            allocator.Add(PduRuntime.GetBinaryForBool(obj.ok), parentOff + 0);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.data.Count), parentOff + 4);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 4 + 4);
                for (var i = 0; i < obj.data.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForUInt8(obj.data[i]));
                }
            }
            allocator.Add(PduRuntime.GetBinaryForString(obj.message, 128), parentOff + 12);
        }
    }
}
