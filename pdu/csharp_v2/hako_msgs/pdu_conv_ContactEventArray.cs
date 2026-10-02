using System;
using System.Collections.Generic;

using Hakoniwa.Pdu.CSharpV2;
using Hakoniwa.Pdu.CSharpV2.hako_msgs;

namespace Hakoniwa.Pdu.CSharpV2.hako_msgs
{
    public static class ContactEventArrayConverter
    {
        public static ContactEventArray PduToMsg(byte[] binaryData)
        {
            var obj = new ContactEventArray();
            var meta = PduMetaData.Parse(binaryData);
            BinaryReadRecursive(meta, binaryData, obj, PduMetaData.PduMetaDataSize);
            return obj;
        }

        public static byte[] MsgToPdu(ContactEventArray obj)
        {
            var baseAllocator = new DynamicAllocator();
            var writer = new BinaryWriterContainer();
            BinaryWriteRecursive(0, writer, baseAllocator, obj);
            return PduRuntime.BuildPdu(baseAllocator, writer);
        }

        public static void BinaryReadRecursive(PduMetaData meta, byte[] binaryData, ContactEventArray obj, int baseOff)
        {
            obj.events = new List<ContactEvent>();
            {
                var arraySize = PduRuntime.ReadInt32(binaryData, baseOff + 0);
                var offsetFromHeap = PduRuntime.ReadInt32(binaryData, baseOff + 0 + 4);
                for (var i = 0; i < arraySize; i++) {
                    var tmp = new ContactEvent();
                    ContactEventConverter.BinaryReadRecursive(meta, binaryData, tmp, meta.HeapOff + offsetFromHeap + (i * 432));
                    obj.events.Add(tmp);
                }
            }
        }

        public static void BinaryWriteRecursive(int parentOff, BinaryWriterContainer writer, DynamicAllocator allocator, ContactEventArray obj)
        {
            {
                var offsetFromHeap = writer.HeapAllocator.Size();
                var arraySize = obj.events.Count;
                allocator.Add(PduRuntime.GetBinaryForInt32(arraySize), parentOff + 0);
                allocator.Add(PduRuntime.GetBinaryForInt32(offsetFromHeap), parentOff + 0 + 4);
                writer.HeapAllocator.Add(new byte[arraySize * 432], offsetFromHeap);
                for (var i = 0; i < arraySize; i++) {
                    ContactEventConverter.BinaryWriteRecursive(offsetFromHeap + (i * 432), writer, writer.HeapAllocator, obj.events[i]);
                }
            }
        }
    }
}
