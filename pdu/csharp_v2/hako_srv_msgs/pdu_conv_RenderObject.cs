using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_srv_msgs;
using Hakoniwa.Pdu.CSharpV2.geometry_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_srv_msgs
{
    public static class RenderObjectConverter
    {
        public static RenderObject PduToMsg(byte[] binaryData)
        {
            var obj = new RenderObject();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(RenderObject obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, RenderObject obj, int baseOff)
        {
            obj.name = PduRuntime.ReadString(binaryData, baseOff + 0, 128);
            obj.model = PduRuntime.ReadString(binaryData, baseOff + 128, 128);
            obj.pose = new Pose();
            PoseConverter.BinaryReadRecursive(meta, binaryData, obj.pose, baseOff + 256);
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, RenderObject obj)
        {
            allocator.Add(PduRuntime.GetBinaryForString(obj.name, 128), parentOff + 0);
            allocator.Add(PduRuntime.GetBinaryForString(obj.model, 128), parentOff + 128);
            PoseConverter.BinaryWriteRecursive(parentOff + 256, writer, allocator, obj.pose);
        }
    }
}
