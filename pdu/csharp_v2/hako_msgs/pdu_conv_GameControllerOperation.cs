using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class GameControllerOperationConverter
    {
        public static GameControllerOperation PduToMsg(byte[] binaryData)
        {
            var obj = new GameControllerOperation();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(GameControllerOperation obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, GameControllerOperation obj, int baseOff)
        {
            obj.axis = new List<double>();
            for (var i = 0; i < 6; i++) {
                obj.axis.Add(PduRuntime.ReadFloat64(binaryData, baseOff + 0 + (i * 8)));
            }
            obj.button = new List<bool>();
            for (var i = 0; i < 15; i++) {
                obj.button.Add(PduRuntime.ReadBool(binaryData, baseOff + 48 + (i * 4)));
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, GameControllerOperation obj)
        {
            for (var i = 0; i < obj.axis.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForFloat64(obj.axis[i]), parentOff + 0 + (i * 8));
            }
            for (var i = 0; i < obj.button.Count; i++) {
                allocator.Add(PduRuntime.GetBinaryForBool(obj.button[i]), parentOff + 48 + (i * 4));
            }
        }
    }
}
