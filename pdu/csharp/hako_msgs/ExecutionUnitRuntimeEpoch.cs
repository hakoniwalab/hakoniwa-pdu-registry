using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_msgs
{
    public class ExecutionUnitRuntimeEpoch
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public ExecutionUnitRuntimeEpoch(IPdu pdu)
        {
            _pdu = pdu;
        }
        public byte[] epoch
        {
            get => _pdu.GetDataArray<byte>("epoch");
            set => _pdu.SetData("epoch", value);
        }
    }
}
