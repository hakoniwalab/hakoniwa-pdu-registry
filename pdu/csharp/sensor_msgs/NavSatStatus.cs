using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.sensor_msgs
{
    public class NavSatStatus
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public NavSatStatus(IPdu pdu)
        {
            _pdu = pdu;
        }
        public sbyte status
        {
            get => _pdu.GetData<sbyte>("status");
            set => _pdu.SetData("status", value);
        }
        public ushort service
        {
            get => _pdu.GetData<ushort>("service");
            set => _pdu.SetData("service", value);
        }
    }
}
