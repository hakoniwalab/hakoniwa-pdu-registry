using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_msgs
{
    public class ExecutionUnitRuntimeContext
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public ExecutionUnitRuntimeContext(IPdu pdu)
        {
            _pdu = pdu;
        }
        public uint config_hash
        {
            get => _pdu.GetData<uint>("config_hash");
            set => _pdu.SetData("config_hash", value);
        }
        public byte epoch
        {
            get => _pdu.GetData<byte>("epoch");
            set => _pdu.SetData("epoch", value);
        }
        public byte owner_id
        {
            get => _pdu.GetData<byte>("owner_id");
            set => _pdu.SetData("owner_id", value);
        }
        public byte[] context
        {
            get => _pdu.GetDataArray<byte>("context");
            set => _pdu.SetData("context", value);
        }
    }
}
