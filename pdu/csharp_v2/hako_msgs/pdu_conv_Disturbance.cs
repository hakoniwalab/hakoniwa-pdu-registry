using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class DisturbanceConverter
    {
        public static Disturbance PduToMsg(byte[] binaryData)
        {
            var obj = new Disturbance();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(Disturbance obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, Disturbance obj, int baseOff)
        {
            obj.d_temp = new DisturbanceTemperature();
            DisturbanceTemperatureConverter.BinaryReadRecursive(meta, binaryData, obj.d_temp, baseOff + 0);
            obj.d_wind = new DisturbanceWind();
            DisturbanceWindConverter.BinaryReadRecursive(meta, binaryData, obj.d_wind, baseOff + 8);
            obj.d_atm = new DisturbanceAtm();
            DisturbanceAtmConverter.BinaryReadRecursive(meta, binaryData, obj.d_atm, baseOff + 32);
            obj.d_boundary = new DisturbanceBoundary();
            DisturbanceBoundaryConverter.BinaryReadRecursive(meta, binaryData, obj.d_boundary, baseOff + 40);
            obj.d_user_custom = new List<DisturbanceUserCustom>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 88);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 88 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new DisturbanceUserCustom();
                    DisturbanceUserCustomConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 8));
                    obj.d_user_custom.Add(tmp);
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, Disturbance obj)
        {
            DisturbanceTemperatureConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.d_temp);
            DisturbanceWindConverter.BinaryWriteRecursive(parentOff + 8, writer, allocator, obj.d_wind);
            DisturbanceAtmConverter.BinaryWriteRecursive(parentOff + 32, writer, allocator, obj.d_atm);
            DisturbanceBoundaryConverter.BinaryWriteRecursive(parentOff + 40, writer, allocator, obj.d_boundary);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.d_user_custom.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 88);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 88 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 8], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    DisturbanceUserCustomConverter.BinaryWriteRecursive(offsetFromHeap + (i * 8), writer, writer.HeapAllocator, obj.d_user_custom[i]);
                }
            }
        }
    }
}
