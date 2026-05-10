using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.nav_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.nav_msgs
{
    public static class OccupancyGridConverter
    {
        public static OccupancyGrid PduToMsg(byte[] binaryData)
        {
            var obj = new OccupancyGrid();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(OccupancyGrid obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, OccupancyGrid obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.info = new MapMetaData();
            MapMetaDataConverter.BinaryReadRecursive(meta, binaryData, obj.info, baseOff + 136);
            obj.data = new List<sbyte>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 216);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 216 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.data.Add(PduRuntime.ReadInt8(binaryData, meta.HeapOff + offsetFromHeap + (i * 1)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, OccupancyGrid obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            MapMetaDataConverter.BinaryWriteRecursive(parentOff + 136, writer, allocator, obj.info);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.data.Count), parentOff + 216);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 216 + 4);
                for (var i = 0; i < obj.data.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForInt8(obj.data[i]));
                }
            }
        }
    }
}
