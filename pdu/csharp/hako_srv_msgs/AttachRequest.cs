using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_srv_msgs
{
    public class AttachRequest
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public AttachRequest(IPdu pdu)
        {
            _pdu = pdu;
        }
        public string asset_name
        {
            get => _pdu.GetData<string>("asset_name");
            set => _pdu.SetData("asset_name", value);
        }
        public ulong delta_asset_tick
        {
            get => _pdu.GetData<ulong>("delta_asset_tick");
            set => _pdu.SetData("delta_asset_tick", value);
        }
    }
}
