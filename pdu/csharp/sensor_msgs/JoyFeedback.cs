using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.sensor_msgs
{
    public class JoyFeedback
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public JoyFeedback(IPdu pdu)
        {
            _pdu = pdu;
        }
        public byte type
        {
            get => _pdu.GetData<byte>("type");
            set => _pdu.SetData("type", value);
        }
        public byte id
        {
            get => _pdu.GetData<byte>("id");
            set => _pdu.SetData("id", value);
        }
        public float intensity
        {
            get => _pdu.GetData<float>("intensity");
            set => _pdu.SetData("intensity", value);
        }
    }
}
