using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_srv_msgs
{
    public class DetachRequest
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public DetachRequest(IPdu pdu)
        {
            _pdu = pdu;
        }
        public ulong session_id
        {
            get => _pdu.GetData<ulong>("session_id");
            set => _pdu.SetData("session_id", value);
        }
    }
}
