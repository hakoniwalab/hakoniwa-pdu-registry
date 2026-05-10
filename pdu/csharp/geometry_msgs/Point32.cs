using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.geometry_msgs
{
    public class Point32
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public Point32(IPdu pdu)
        {
            _pdu = pdu;
        }
        public float x
        {
            get => _pdu.GetData<float>("x");
            set => _pdu.SetData("x", value);
        }
        public float y
        {
            get => _pdu.GetData<float>("y");
            set => _pdu.SetData("y", value);
        }
        public float z
        {
            get => _pdu.GetData<float>("z");
            set => _pdu.SetData("z", value);
        }
    }
}
