using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_msgs
{
    public class ExecutionUnitRuntimeNode
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public ExecutionUnitRuntimeNode(IPdu pdu)
        {
            _pdu = pdu;
        }
        public uint node_id
        {
            get => _pdu.GetData<uint>("node_id");
            set => _pdu.SetData("node_id", value);
        }
    }
}
