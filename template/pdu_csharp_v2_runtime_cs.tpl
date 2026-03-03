using System;
using System.Buffers.Binary;
using System.Collections.Generic;
using System.Text;
using System.Text.Json;

namespace Hakoniwa.Pdu.CSharpV2
{
    public sealed class PduMetaData
    {
        public const int PduMetaDataSize = 24;
        public const uint MagicNo = 0x12345678;
        public const uint Version = 1;

        public uint Magic { get; set; } = MagicNo;
        public uint Ver { get; set; } = Version;
        public int BaseOff { get; set; } = PduMetaDataSize;
        public int HeapOff { get; set; }
        public int TotalSize { get; set; }

        public byte[] ToBytes()
        {
            var buffer = new byte[PduMetaDataSize];
            BinaryPrimitives.WriteUInt32LittleEndian(buffer.AsSpan(0, 4), Magic);
            BinaryPrimitives.WriteUInt32LittleEndian(buffer.AsSpan(4, 4), Ver);
            BinaryPrimitives.WriteInt32LittleEndian(buffer.AsSpan(8, 4), BaseOff);
            BinaryPrimitives.WriteInt32LittleEndian(buffer.AsSpan(12, 4), HeapOff);
            BinaryPrimitives.WriteInt32LittleEndian(buffer.AsSpan(16, 4), TotalSize);
            return buffer;
        }

        public static PduMetaData Parse(byte[] binary)
        {
            if (binary.Length < PduMetaDataSize) {
                throw new ArgumentException("PDU binary too small");
            }
            var meta = new PduMetaData
            {
                Magic = BinaryPrimitives.ReadUInt32LittleEndian(binary.AsSpan(0, 4)),
                Ver = BinaryPrimitives.ReadUInt32LittleEndian(binary.AsSpan(4, 4)),
                BaseOff = BinaryPrimitives.ReadInt32LittleEndian(binary.AsSpan(8, 4)),
                HeapOff = BinaryPrimitives.ReadInt32LittleEndian(binary.AsSpan(12, 4)),
                TotalSize = BinaryPrimitives.ReadInt32LittleEndian(binary.AsSpan(16, 4)),
            };
            if (meta.Magic != MagicNo || meta.Ver != Version) {
                throw new ArgumentException("Invalid PDU metadata");
            }
            return meta;
        }
    }

    public sealed class DynamicAllocator
    {
        private readonly List<byte> _data = new();

        public int Add(byte[] bytes, int? expectedOffset = null)
        {
            var offset = expectedOffset ?? _data.Count;
            EnsureSize(offset + bytes.Length);
            for (var i = 0; i < bytes.Length; i++) {
                _data[offset + i] = bytes[i];
            }
            return offset;
        }

        public byte[] ToArray() => _data.ToArray();
        public int Size() => _data.Count;

        private void EnsureSize(int size)
        {
            while (_data.Count < size) {
                _data.Add(0);
            }
        }
    }

    public sealed class BinaryWriterContainer
    {
        public PduMetaData Meta { get; } = new();
        public DynamicAllocator HeapAllocator { get; } = new();
    }

    public static class PduRuntime
    {
        public static byte[] ReadBinary(byte[] binary, int offset, int size)
        {
            var result = new byte[size];
            Buffer.BlockCopy(binary, offset, result, 0, size);
            return result;
        }

        public static void WriteBinary(byte[] binary, int offset, byte[] value)
        {
            Buffer.BlockCopy(value, 0, binary, offset, value.Length);
        }

        public static byte[] BuildPdu(DynamicAllocator baseAllocator, BinaryWriterContainer container)
        {
            var totalSize = PduMetaData.PduMetaDataSize + baseAllocator.Size() + container.HeapAllocator.Size();
            container.Meta.HeapOff = PduMetaData.PduMetaDataSize + baseAllocator.Size();
            container.Meta.TotalSize = totalSize;

            var binary = new byte[totalSize];
            WriteBinary(binary, 0, container.Meta.ToBytes());
            WriteBinary(binary, container.Meta.BaseOff, baseAllocator.ToArray());
            WriteBinary(binary, container.Meta.HeapOff, container.HeapAllocator.ToArray());
            return binary;
        }

        public static bool ReadBool(byte[] binary, int offset) => ReadInt32(binary, offset) != 0;
        public static sbyte ReadInt8(byte[] binary, int offset) => unchecked((sbyte)binary[offset]);
        public static byte ReadUInt8(byte[] binary, int offset) => binary[offset];
        public static short ReadInt16(byte[] binary, int offset) => BinaryPrimitives.ReadInt16LittleEndian(binary.AsSpan(offset, 2));
        public static ushort ReadUInt16(byte[] binary, int offset) => BinaryPrimitives.ReadUInt16LittleEndian(binary.AsSpan(offset, 2));
        public static int ReadInt32(byte[] binary, int offset) => BinaryPrimitives.ReadInt32LittleEndian(binary.AsSpan(offset, 4));
        public static uint ReadUInt32(byte[] binary, int offset) => BinaryPrimitives.ReadUInt32LittleEndian(binary.AsSpan(offset, 4));
        public static long ReadInt64(byte[] binary, int offset) => BinaryPrimitives.ReadInt64LittleEndian(binary.AsSpan(offset, 8));
        public static ulong ReadUInt64(byte[] binary, int offset) => BinaryPrimitives.ReadUInt64LittleEndian(binary.AsSpan(offset, 8));
        public static float ReadFloat32(byte[] binary, int offset) => BitConverter.ToSingle(binary, offset);
        public static double ReadFloat64(byte[] binary, int offset) => BitConverter.ToDouble(binary, offset);
        public static string ReadString(byte[] binary, int offset, int size)
        {
            var slice = ReadBinary(binary, offset, size);
            var end = Array.IndexOf(slice, (byte)0);
            if (end < 0) {
                end = slice.Length;
            }
            return Encoding.UTF8.GetString(slice, 0, end);
        }

        public static byte[] GetBinaryForString(string value, int size)
        {
            var raw = Encoding.UTF8.GetBytes(value ?? string.Empty);
            var buffer = new byte[size];
            var copyLen = Math.Min(raw.Length, Math.Max(0, size - 1));
            Buffer.BlockCopy(raw, 0, buffer, 0, copyLen);
            if (size > 0) {
                buffer[Math.Min(copyLen, size - 1)] = 0;
            }
            return buffer;
        }

        public static byte[] GetBinaryForBool(bool value) => GetBinaryForInt32(value ? 1 : 0);
        public static byte[] GetBinaryForInt8(sbyte value) => new[] { unchecked((byte)value) };
        public static byte[] GetBinaryForUInt8(byte value) => new[] { value };
        public static byte[] GetBinaryForInt16(short value) { var b = new byte[2]; BinaryPrimitives.WriteInt16LittleEndian(b, value); return b; }
        public static byte[] GetBinaryForUInt16(ushort value) { var b = new byte[2]; BinaryPrimitives.WriteUInt16LittleEndian(b, value); return b; }
        public static byte[] GetBinaryForInt32(int value) { var b = new byte[4]; BinaryPrimitives.WriteInt32LittleEndian(b, value); return b; }
        public static byte[] GetBinaryForUInt32(uint value) { var b = new byte[4]; BinaryPrimitives.WriteUInt32LittleEndian(b, value); return b; }
        public static byte[] GetBinaryForInt64(long value) { var b = new byte[8]; BinaryPrimitives.WriteInt64LittleEndian(b, value); return b; }
        public static byte[] GetBinaryForUInt64(ulong value) { var b = new byte[8]; BinaryPrimitives.WriteUInt64LittleEndian(b, value); return b; }
        public static byte[] GetBinaryForFloat32(float value) => BitConverter.GetBytes(value);
        public static byte[] GetBinaryForFloat64(double value) => BitConverter.GetBytes(value);

        public static T ConvertValue<T>(object? value)
        {
            if (value is JsonElement element) {
                value = JsonElementToObject(element);
            }
            return (T)Convert.ChangeType(value!, typeof(T));
        }

        public static T ConvertObject<T>(object? value, Func<Dictionary<string, object?>, T> factory)
        {
            if (value is JsonElement element) {
                value = JsonElementToObject(element);
            }
            return factory((Dictionary<string, object?>)value!);
        }

        public static List<T> ConvertList<T>(object? value)
        {
            if (value is JsonElement element) {
                value = JsonElementToObject(element);
            }
            var result = new List<T>();
            foreach (var item in (IEnumerable<object?>)value!) {
                if (item is JsonElement jsonElement) {
                    result.Add(ConvertValue<T>(jsonElement));
                }
                else {
                    result.Add((T)Convert.ChangeType(item!, typeof(T)));
                }
            }
            return result;
        }

        public static List<T> ConvertObjectList<T>(object? value, Func<Dictionary<string, object?>, T> factory)
        {
            if (value is JsonElement element) {
                value = JsonElementToObject(element);
            }
            var result = new List<T>();
            foreach (var item in (IEnumerable<object?>)value!) {
                if (item is JsonElement jsonElement) {
                    result.Add(factory(JsonElementToDictionary(jsonElement)));
                }
                else {
                    result.Add(factory((Dictionary<string, object?>)item!));
                }
            }
            return result;
        }

        public static Dictionary<string, object?> JsonElementToDictionary(JsonElement element)
        {
            var dict = new Dictionary<string, object?>();
            foreach (var property in element.EnumerateObject()) {
                dict[property.Name] = JsonElementToObject(property.Value);
            }
            return dict;
        }

        public static object? JsonElementToObject(JsonElement element)
        {
            return element.ValueKind switch
            {
                JsonValueKind.Object => JsonElementToDictionary(element),
                JsonValueKind.Array => JsonElementToList(element),
                JsonValueKind.String => element.GetString(),
                JsonValueKind.Number when element.TryGetInt64(out var l) => l,
                JsonValueKind.Number => element.GetDouble(),
                JsonValueKind.True => true,
                JsonValueKind.False => false,
                JsonValueKind.Null => null,
                _ => null,
            };
        }

        public static List<object?> JsonElementToList(JsonElement element)
        {
            var list = new List<object?>();
            foreach (var item in element.EnumerateArray()) {
                list.Add(JsonElementToObject(item));
            }
            return list;
        }
    }
}
