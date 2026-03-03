using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.sensor_msgs;
using Hakoniwa.Pdu.CSharpV2.std_msgs;

namespace Hakoniwa.Pdu.CSharpV2.sensor_msgs
{
    public static class CameraInfoConverter
    {
        public static CameraInfo PduToMsg(byte[] binaryData)
        {
            var obj = new CameraInfo();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(CameraInfo obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, CameraInfo obj, int baseOff)
        {
            obj.header = new Header();
            HeaderConverter.BinaryReadRecursive(meta, binaryData, obj.header, baseOff + 0);
            obj.height = PduRuntime.ReadUInt32(binaryData, baseOff + 136);
            obj.width = PduRuntime.ReadUInt32(binaryData, baseOff + 140);
            obj.distortion_model = PduRuntime.ReadString(binaryData, baseOff + 144, 128);
            obj.d = new List<double>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 272);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 272 + 4);
                for (var i = 0; i < arraySize; i++) {
                    obj.d.Add(PduRuntime.ReadFloat64(binaryData, meta.HeapOff + offsetFromHeap + (i * 8)));
                }
            }
            obj.k = new List<double>();
            for (var i = 0; i < 9; i++) {
                obj.k.Add(PduRuntime.ReadFloat64(binaryData, baseOff + 280 + (i * 8)));
            }
            obj.r = new List<double>();
            for (var i = 0; i < 9; i++) {
                obj.r.Add(PduRuntime.ReadFloat64(binaryData, baseOff + 352 + (i * 8)));
            }
            obj.p = new List<double>();
            for (var i = 0; i < 12; i++) {
                obj.p.Add(PduRuntime.ReadFloat64(binaryData, baseOff + 424 + (i * 8)));
            }
            obj.binning_x = PduRuntime.ReadUInt32(binaryData, baseOff + 520);
            obj.binning_y = PduRuntime.ReadUInt32(binaryData, baseOff + 524);
            obj.roi = new RegionOfInterest();
            RegionOfInterestConverter.BinaryReadRecursive(meta, binaryData, obj.roi, baseOff + 528);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, CameraInfo obj)
        {
            HeaderConverter.BinaryWriteRecursive(parentOff + 0, writer, allocator, obj.header);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.height), parentOff + 136);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.width), parentOff + 140);
            allocator.Add(PduRuntime.GetBinaryForString(obj.distortion_model, 128), parentOff + 144);
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                allocator.Add(PduRuntime.GetBinaryForInt32(obj.d.Count), parentOff + 272);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 272 + 4);
                for (var i = 0; i < obj.d.Count; i++) {
                    writer.HeapAllocator.Add(PduRuntime.GetBinaryForFloat64(obj.d[i]));
                }
            }
            for (var i = 0; i < obj.k.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForFloat64(obj.k[i]), parentOff + 280 + (i * 8));
            }
            for (var i = 0; i < obj.r.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForFloat64(obj.r[i]), parentOff + 352 + (i * 8));
            }
            for (var i = 0; i < obj.p.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForFloat64(obj.p[i]), parentOff + 424 + (i * 8));
            }
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.binning_x), parentOff + 520);
            allocator.Add(PduRuntime.GetBinaryForUInt32(obj.binning_y), parentOff + 524);
            RegionOfInterestConverter.BinaryWriteRecursive(parentOff + 528, writer, allocator, obj.roi);
        }
    }
}
