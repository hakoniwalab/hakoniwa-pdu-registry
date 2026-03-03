using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class PointCloud2Converter
    {
        public static PointCloud2 PduToMsg(byte[] binaryData)
        {
            var obj = new PointCloud2();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(PointCloud2 obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, PointCloud2 obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.height = PduRuntime.ReadUInt32(binaryData, baseOff + 136);
            obj.width = PduRuntime.ReadUInt32(binaryData, baseOff + 140);
            obj.fields = new List<PointField>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 144);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 144 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new PointField();
                    PointFieldConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 140));
                    obj.fields.Add(tmp);
                }
            }
            obj.is_bigendian = PduRuntime.ReadBool(binaryData, baseOff + 152);
            obj.point_step = PduRuntime.ReadUInt32(binaryData, baseOff + 156);
            obj.row_step = PduRuntime.ReadUInt32(binaryData, baseOff + 160);
            obj.data = new List<byte>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 164);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 164 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.data.Add(PduRuntime.ReadUInt8(binaryData, meta.HeapOff + offsetFromHeap + (i * 1)));
                }
            }
            obj.is_dense = PduRuntime.ReadBool(binaryData, baseOff + 172);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, PointCloud2 obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.height), parentOff + 136);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.width), parentOff + 140);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.fields.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 144);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 144 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 140], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    PointFieldConverter.BinaryWriteRecursive(offsetFromHeap + (i * 140), writer, writer.HeapAllocator, obj.fields[i]);
                }
            }
            allocator.Add(PduRuntime.GetBinaryForBool(obj.is_bigendian), parentOff + 152);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.point_step), parentOff + 156);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.row_step), parentOff + 160);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.data.Count), parentOff + 164);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 164 + 4);
                for (var i = 0; i < obj.data.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForUInt8(obj.data[i]));
                }
            }
            allocator.Add(PduRuntime.GetBinaryForBool(obj.is_dense), parentOff + 172);
        }
    }
}
