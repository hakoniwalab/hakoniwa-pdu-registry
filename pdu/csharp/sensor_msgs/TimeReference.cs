using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.sensor_msgs
{
    public class TimeReference
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public TimeReference(IPdu pdu)
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
        private Time _time_ref;
        public Time time_ref
        {
            get
            {
                if (_time_ref == null)
                {
                    _time_ref = new Time(_pdu.GetData<IPdu>("time_ref"));
                }
                return _time_ref;
            }
            set
            {
                _time_ref = value;
                _pdu.SetData("time_ref", value.GetPdu());
            }
        }
        public string source
        {
            get => _pdu.GetData<string>("source");
            set => _pdu.SetData("source", value);
        }
    }
}
