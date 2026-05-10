using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.geometry_msgs
{
    public class Vector3Stamped
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public Vector3Stamped(IPdu pdu)
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
        private Vector3 _vector;
        public Vector3 vector
        {
            get
            {
                if (_vector == null)
                {
                    _vector = new Vector3(_pdu.GetData<IPdu>("vector"));
                }
                return _vector;
            }
            set
            {
                _vector = value;
                _pdu.SetData("vector", value.GetPdu());
            }
        }
    }
}
