using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.sensor_msgs
{
    public class ChannelFloat32
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public ChannelFloat32(IPdu pdu)
        {
            _pdu = pdu;
        }
        public string name
        {
            get => _pdu.GetData<string>("name");
            set => _pdu.SetData("name", value);
        }
        public float[] values
        {
            get => _pdu.GetDataArray<float>("values");
            set => _pdu.SetData("values", value);
        }
    }
}
