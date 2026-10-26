using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_srv_msgs
{
    public class SetLightRequest
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public SetLightRequest(IPdu pdu)
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
        public double flashing_on_s
        {
            get => _pdu.GetData<double>("flashing_on_s");
            set => _pdu.SetData("flashing_on_s", value);
        }
        public double flashing_off_s
        {
            get => _pdu.GetData<double>("flashing_off_s");
            set => _pdu.SetData("flashing_off_s", value);
        }
        public double transition_s
        {
            get => _pdu.GetData<double>("transition_s");
            set => _pdu.SetData("transition_s", value);
        }
    }
}
