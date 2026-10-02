using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.geometry_msgs;

namespace hakoniwa.pdu.msgs.hako_msgs
{
    public class ContactEvent
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public ContactEvent(IPdu pdu)
        {
            _pdu = pdu;
        }
        private Time _stamp;
        public Time stamp
        {
            get
            {
                if (_stamp == null)
                {
                    _stamp = new Time(_pdu.GetData<IPdu>("stamp"));
                }
                return _stamp;
            }
            set
            {
                _stamp = value;
                _pdu.SetData("stamp", value.GetPdu());
            }
        }
        public string self_name
        {
            get => _pdu.GetData<string>("self_name");
            set => _pdu.SetData("self_name", value);
        }
        public string other_name
        {
            get => _pdu.GetData<string>("other_name");
            set => _pdu.SetData("other_name", value);
        }
        public string other_kind
        {
            get => _pdu.GetData<string>("other_kind");
            set => _pdu.SetData("other_kind", value);
        }
        private Point _position;
        public Point position
        {
            get
            {
                if (_position == null)
                {
                    _position = new Point(_pdu.GetData<IPdu>("position"));
                }
                return _position;
            }
            set
            {
                _position = value;
                _pdu.SetData("position", value.GetPdu());
            }
        }
        public double relative_speed
        {
            get => _pdu.GetData<double>("relative_speed");
            set => _pdu.SetData("relative_speed", value);
        }
        public bool started
        {
            get => _pdu.GetData<bool>("started");
            set => _pdu.SetData("started", value);
        }
    }
}
