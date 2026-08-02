using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_action_msgs
{
    public class ActionRequestHeader
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public ActionRequestHeader(IPdu pdu)
        {
            _pdu = pdu;
        }
        public byte version
        {
            get => _pdu.GetData<byte>("version");
            set => _pdu.SetData("version", value);
        }
        public byte request_kind
        {
            get => _pdu.GetData<byte>("request_kind");
            set => _pdu.SetData("request_kind", value);
        }
        public byte[] reserved
        {
            get => _pdu.GetDataArray<byte>("reserved");
            set => _pdu.SetData("reserved", value);
        }
        public byte[] goal_id
        {
            get => _pdu.GetDataArray<byte>("goal_id");
            set => _pdu.SetData("goal_id", value);
        }
    }
}
