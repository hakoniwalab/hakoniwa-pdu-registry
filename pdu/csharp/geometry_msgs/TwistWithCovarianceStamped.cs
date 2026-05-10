using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.geometry_msgs
{
    public class TwistWithCovarianceStamped
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public TwistWithCovarianceStamped(IPdu pdu)
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
        private TwistWithCovariance _twist;
        public TwistWithCovariance twist
        {
            get
            {
                if (_twist == null)
                {
                    _twist = new TwistWithCovariance(_pdu.GetData<IPdu>("twist"));
                }
                return _twist;
            }
            set
            {
                _twist = value;
                _pdu.SetData("twist", value.GetPdu());
            }
        }
    }
}
