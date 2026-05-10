using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.sensor_msgs
{
    public class LaserEcho
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public LaserEcho(IPdu pdu)
        {
            _pdu = pdu;
        }
        public float[] echoes
        {
            get => _pdu.GetDataArray<float>("echoes");
            set => _pdu.SetData("echoes", value);
        }
    }
}
