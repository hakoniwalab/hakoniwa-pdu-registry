using System.Buffers.Binary;

namespace Hakoniwa.Pdu.CSharpV2
{
    public enum PduMetaDataState
    {
        Invalid = 0,
        Uninitialized = 1,
        Valid = 2,
    }

    public static class PduMetaDataClassifier
    {
        public static PduMetaDataState Classify(byte[]? binary)
        {
            if (binary == null || binary.Length < PduMetaData.PduMetaDataSize) {
                return PduMetaDataState.Invalid;
            }
            var allZero = true;
            for (var index = 0; index < PduMetaData.PduMetaDataSize; index++) {
                if (binary[index] != 0) {
                    allZero = false;
                    break;
                }
            }
            if (allZero) {
                return PduMetaDataState.Uninitialized;
            }
            var magic = BinaryPrimitives.ReadUInt32LittleEndian(binary.AsSpan(0, 4));
            var version = BinaryPrimitives.ReadUInt32LittleEndian(binary.AsSpan(4, 4));
            return magic == PduMetaData.MagicNo && version == PduMetaData.Version
                ? PduMetaDataState.Valid
                : PduMetaDataState.Invalid;
        }
    }
}
