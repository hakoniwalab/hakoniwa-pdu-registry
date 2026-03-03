using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class DroneVisualStateConverter
    {
        public static DroneVisualState PduToMsg(byte[] binaryData)
        {
            var obj = new DroneVisualState();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(DroneVisualState obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, DroneVisualState obj, int baseOff)
        {
            obj.x = PduRuntime.ReadFloat32(binaryData, baseOff + 0);
            obj.y = PduRuntime.ReadFloat32(binaryData, baseOff + 4);
            obj.z = PduRuntime.ReadFloat32(binaryData, baseOff + 8);
            obj.roll = PduRuntime.ReadFloat32(binaryData, baseOff + 12);
            obj.pitch = PduRuntime.ReadFloat32(binaryData, baseOff + 16);
            obj.yaw = PduRuntime.ReadFloat32(binaryData, baseOff + 20);
            obj.pwm_duty = new List<float>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 24);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 24 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.pwm_duty.Add(PduRuntime.ReadFloat32(binaryData, meta.HeapOff + offsetFromHeap + (i * 4)));
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, DroneVisualState obj)
        {
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.x), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.y), parentOff + 4);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.z), parentOff + 8);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.roll), parentOff + 12);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.pitch), parentOff + 16);
            allocator.Add(PduRuntime.GetBinaryForFloat32(obj.yaw), parentOff + 20);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.pwm_duty.Count), parentOff + 24);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 24 + 4);
                for (var i = 0; i < obj.pwm_duty.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat32(obj.pwm_duty[i]));
                }
            }
        }
    }
}
