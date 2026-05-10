using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.geometry_msgs
{
    public class PointStamped
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public PointStamped(IPdu pdu)
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
        private Point _point;
        public Point point
        {
            get
            {
                if (_point == null)
                {
                    _point = new Point(_pdu.GetData<IPdu>("point"));
                }
                return _point;
            }
            set
            {
                _point = value;
                _pdu.SetData("point", value.GetPdu());
            }
        }
    }
}
