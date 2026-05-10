using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.nav_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.nav_msgs
{
    public static class GridCellsConverter
    {
        public static GridCells PduToMsg(byte[] binaryData)
        {
            var obj = new GridCells();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(GridCells obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, GridCells obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.cell_width = PduRuntime.ReadFloat32(binaryData, baseOff + 136);
            obj.cell_height = PduRuntime.ReadFloat32(binaryData, baseOff + 140);
            obj.cells = new List<Point>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 144);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 144 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new Point();
                    PointConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 24));
                    obj.cells.Add(tmp);
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, GridCells obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.cell_width), parentOff + 136);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.cell_height), parentOff + 140);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.cells.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 144);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 144 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 24], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    PointConverter.BinaryWriteRecursive(offsetFromHeap + (i * 24), writer, writer.HeapAllocator, obj.cells[i]);
                }
            }
        }
    }
}
