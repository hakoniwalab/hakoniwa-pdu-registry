using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class DisturbanceUserCustomConverter
    {
        public static DisturbanceUserCustom PduToMsg(byte[] binaryData)
        {
            var obj = new DisturbanceUserCustom();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(DisturbanceUserCustom obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, DisturbanceUserCustom obj, int baseOff)
        {
            obj.data = new List<double>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 0);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 0 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.data.Add(PduRuntime.ReadFloat64(binaryData, meta.HeapOff + offsetFromHeap + (i * 8)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, DisturbanceUserCustom obj)
        {
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.data.Count), parentOff + 0);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 0 + 4);
                for (var i = 0; i < obj.data.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat64(obj.data[i]));
                }
            }
        }
    }
}
