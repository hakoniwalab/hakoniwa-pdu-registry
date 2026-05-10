using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.geometry_msgs
{
    public class PoseWithCovarianceStamped
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public PoseWithCovarianceStamped(IPdu pdu)
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
        private PoseWithCovariance _pose;
        public PoseWithCovariance pose
        {
            get
            {
                if (_pose == null)
                {
                    _pose = new PoseWithCovariance(_pdu.GetData<IPdu>("pose"));
                }
                return _pose;
            }
            set
            {
                _pose = value;
                _pdu.SetData("pose", value.GetPdu());
            }
        }
    }
}
