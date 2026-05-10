using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.sensor_msgs
{
    public class Range
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public Range(IPdu pdu)
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
        public byte radiation_type
        {
            get => _pdu.GetData<byte>("radiation_type");
            set => _pdu.SetData("radiation_type", value);
        }
        public float field_of_view
        {
            get => _pdu.GetData<float>("field_of_view");
            set => _pdu.SetData("field_of_view", value);
        }
        public float min_range
        {
            get => _pdu.GetData<float>("min_range");
            set => _pdu.SetData("min_range", value);
        }
        public float max_range
        {
            get => _pdu.GetData<float>("max_range");
            set => _pdu.SetData("max_range", value);
        }
        public float range
        {
            get => _pdu.GetData<float>("range");
            set => _pdu.SetData("range", value);
        }
    }
}
