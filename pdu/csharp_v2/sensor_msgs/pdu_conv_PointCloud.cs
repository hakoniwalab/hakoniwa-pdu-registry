using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class PointCloudConverter
    {
        public static PointCloud PduToMsg(byte[] binaryData)
        {
            var obj = new PointCloud();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(PointCloud obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, PointCloud obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.points = new List<Point32>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 136);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 136 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new Point32();
                    Point32Converter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 12));
                    obj.points.Add(tmp);
                }
            }
            obj.channels = new List<ChannelFloat32>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 144);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 144 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new ChannelFloat32();
                    ChannelFloat32Converter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 136));
                    obj.channels.Add(tmp);
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, PointCloud obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.points.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 136);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 136 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 12], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    Point32Converter.BinaryWriteRecursive(offsetFromHeap + (i * 12), writer, writer.HeapAllocator, obj.points[i]);
                }
            }
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.channels.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 144);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 144 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 136], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    ChannelFloat32Converter.BinaryWriteRecursive(offsetFromHeap + (i * 136), writer, writer.HeapAllocator, obj.channels[i]);
                }
            }
        }
    }
}
