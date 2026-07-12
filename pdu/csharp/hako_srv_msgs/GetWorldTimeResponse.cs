using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_srv_msgs
{
    public class GetWorldTimeResponse
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public GetWorldTimeResponse(IPdu pdu)
        {
            _pdu = pdu;
        }
        public uint result_code
        {
            get => _pdu.GetData<uint>("result_code");
            set => _pdu.SetData("result_code", value);
        }
        private LogicalTime _world_time;
        public LogicalTime world_time
        {
            get
            {
                if (_world_time == null)
                {
                    _world_time = new LogicalTime(_pdu.GetData<IPdu>("world_time"));
                }
                return _world_time;
            }
            set
            {
                _world_time = value;
                _pdu.SetData("world_time", value.GetPdu());
            }
        }
    }
}
