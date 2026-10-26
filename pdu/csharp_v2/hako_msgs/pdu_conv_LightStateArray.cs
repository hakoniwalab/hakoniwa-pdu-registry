using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class LightStateArrayConverter
    {
        public static LightStateArray PduToMsg(byte[] binaryData)
        {
            var obj = new LightStateArray();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(LightStateArray obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, LightStateArray obj, int baseOff)
        {
            obj.stamp_usec = PduRuntime.ReadUInt64(binaryData, baseOff + 0);
            obj.carrier = PduRuntime.ReadString(binaryData, baseOff + 8, 128);
            obj.lights = new List<LightState>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 136);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 136 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new LightState();
                    LightStateConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 152));
                    obj.lights.Add(tmp);
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, LightStateArray obj)
        {
            allocator.Add(PduRuntime.GetBinaryForUInt64(obj.stamp_usec), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForString(obj.carrier, 128), parentOff + 8);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.lights.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 136);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 136 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 152], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    LightStateConverter.BinaryWriteRecursive(offsetFromHeap + (i * 152), writer, writer.HeapAllocator, obj.lights[i]);
                }
            }
        }
    }
}
