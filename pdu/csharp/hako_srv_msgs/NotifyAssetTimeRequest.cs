using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_srv_msgs
{
    public class NotifyAssetTimeRequest
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public NotifyAssetTimeRequest(IPdu pdu)
        {
            _pdu = pdu;
        }
        public ulong session_id
        {
            get => _pdu.GetData<ulong>("session_id");
            set => _pdu.SetData("session_id", value);
        }
        private LogicalTime _asset_time;
        public LogicalTime asset_time
        {
            get
            {
                if (_asset_time == null)
                {
                    _asset_time = new LogicalTime(_pdu.GetData<IPdu>("asset_time"));
                }
                return _asset_time;
            }
            set
            {
                _asset_time = value;
                _pdu.SetData("asset_time", value.GetPdu());
            }
        }
    }
}
