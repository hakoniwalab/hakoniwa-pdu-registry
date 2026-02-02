using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_msgs
{
    public class ExecutionUnitRuntimeStatus
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public ExecutionUnitRuntimeStatus(IPdu pdu)
        {
            _pdu = pdu;
        }
        public uint config_hash
        {
            get => _pdu.GetData<uint>("config_hash");
            set => _pdu.SetData("config_hash", value);
        }
        public ushort unit_count
        {
            get => _pdu.GetData<ushort>("unit_count");
            set => _pdu.SetData("unit_count", value);
        }
        public byte[] status
        {
            get => _pdu.GetDataArray<byte>("status");
            set => _pdu.SetData("status", value);
        }
        public byte[] epoch
        {
            get => _pdu.GetDataArray<byte>("epoch");
            set => _pdu.SetData("epoch", value);
        }
        public byte[] curr_owner_node_id
        {
            get => _pdu.GetDataArray<byte>("curr_owner_node_id");
            set => _pdu.SetData("curr_owner_node_id", value);
        }
        public byte[] next_owner_node_id
        {
            get => _pdu.GetDataArray<byte>("next_owner_node_id");
            set => _pdu.SetData("next_owner_node_id", value);
        }
    }
}
