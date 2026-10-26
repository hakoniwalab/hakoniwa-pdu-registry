using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_msgs
{
    public class LightState
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public LightState(IPdu pdu)
        {
            _pdu = pdu;
        }
        public string source
        {
            get => _pdu.GetData<string>("source");
            set => _pdu.SetData("source", value);
        }
        public byte mode
        {
            get => _pdu.GetData<byte>("mode");
            set => _pdu.SetData("mode", value);
        }
        public double luminous_intensity_scale
        {
            get => _pdu.GetData<double>("luminous_intensity_scale");
            set => _pdu.SetData("luminous_intensity_scale", value);
        }
        public bool is_lit
        {
            get => _pdu.GetData<bool>("is_lit");
            set => _pdu.SetData("is_lit", value);
        }
    }
}
