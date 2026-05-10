using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.geometry_msgs
{
    public class InertiaStamped
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public InertiaStamped(IPdu pdu)
        {
            _pdu = pdu;
        }
        private Header _header;
        public Header header
        {
            get
            {
                if (_header == null)
                {
                    _header = new Header(_pdu.GetData<IPdu>("header"));
                }
                return _header;
            }
            set
            {
                _header = value;
                _pdu.SetData("header", value.GetPdu());
            }
        }
        private Inertia _inertia;
        public Inertia inertia
        {
            get
            {
                if (_inertia == null)
                {
                    _inertia = new Inertia(_pdu.GetData<IPdu>("inertia"));
                }
                return _inertia;
            }
            set
            {
                _inertia = value;
                _pdu.SetData("inertia", value.GetPdu());
            }
        }
    }
}
