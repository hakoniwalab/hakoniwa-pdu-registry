using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class ImageConverter
    {
        public static Image PduToMsg(byte[] binaryData)
        {
            var obj = new Image();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Image obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Image obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.height = PduRuntime.ReadUInt32(binaryData, baseOff + 136);
            obj.width = PduRuntime.ReadUInt32(binaryData, baseOff + 140);
            obj.encoding = PduRuntime.ReadString(binaryData, baseOff + 144, 128);
            obj.is_bigendian = PduRuntime.ReadUInt8(binaryData, baseOff + 272);
            obj.step = PduRuntime.ReadUInt32(binaryData, baseOff + 276);
            obj.data = new List<byte>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 280);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 280 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.data.Add(PduRuntime.ReadUInt8(binaryData, meta.HeapOff + offsetFromHeap + (i * 1)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Image obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.height), parentOff + 136);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.width), parentOff + 140);
            allocator.Add(PduRuntime.GetBinaryForString(obj.encoding, 128), parentOff + 144);
            allocator.Add(PduRuntime.GetBinaryForUInt8(obj.is_bigendian), parentOff + 272);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.step), parentOff + 276);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.data.Count), parentOff + 280);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 280 + 4);
                for (var i = 0; i < obj.data.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForUInt8(obj.data[i]));
                }
            }
        }
    }
}
