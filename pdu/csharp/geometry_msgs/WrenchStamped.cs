using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.geometry_msgs
{
    public class WrenchStamped
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public WrenchStamped(IPdu pdu)
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
        private Wrench _wrench;
        public Wrench wrench
        {
            get
            {
                if (_wrench == null)
                {
                    _wrench = new Wrench(_pdu.GetData<IPdu>("wrench"));
                }
                return _wrench;
            }
            set
            {
                _wrench = value;
                _pdu.SetData("wrench", value.GetPdu());
            }
        }
    }
}
