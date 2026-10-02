using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.geometry_msgs;

namespace hakoniwa.pdu.msgs.hako_msgs
{
    public class ContactEventArray
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public ContactEventArray(IPdu pdu)
        {
            _pdu = pdu;
        }
        private ContactEvent[] _events;
        public ContactEvent[] events
        {
            get
            {
                if (_events == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("events");
                    _events = new ContactEvent[fieldPdus.Length];
                    ContactEvent[] result = new ContactEvent[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _events[i] = new ContactEvent(fieldPdus[i]);
                    }
                }
                return _events;
            }
            set
            {
                _events = new ContactEvent[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _events[i] = value[i];
                }
                _pdu.SetData("events", fieldPdus);
            }
        }
    }
}
