using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_srv_msgs
{
    public class LogicalTime
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public LogicalTime(IPdu pdu)
        {
            _pdu = pdu;
        }
        public ulong generation
        {
            get => _pdu.GetData<ulong>("generation");
            set => _pdu.SetData("generation", value);
        }
        public ulong offset_tick
        {
            get => _pdu.GetData<ulong>("offset_tick");
            set => _pdu.SetData("offset_tick", value);
        }
    }
}
