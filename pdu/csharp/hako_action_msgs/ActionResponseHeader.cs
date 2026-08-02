using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_action_msgs
{
    public class ActionResponseHeader
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public ActionResponseHeader(IPdu pdu)
        {
            _pdu = pdu;
        }
        public byte version
        {
            get => _pdu.GetData<byte>("version");
            set => _pdu.SetData("version", value);
        }
        public byte response_kind
        {
            get => _pdu.GetData<byte>("response_kind");
            set => _pdu.SetData("response_kind", value);
        }
        public byte status
        {
            get => _pdu.GetData<byte>("status");
            set => _pdu.SetData("status", value);
        }
        public byte reserved
        {
            get => _pdu.GetData<byte>("reserved");
            set => _pdu.SetData("reserved", value);
        }
        public byte[] goal_id
        {
            get => _pdu.GetDataArray<byte>("goal_id");
            set => _pdu.SetData("goal_id", value);
        }
    }
}
