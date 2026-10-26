using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.geometry_msgs;

namespace hakoniwa.pdu.msgs.hako_srv_msgs
{
    public class PersonStepRequest
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public PersonStepRequest(IPdu pdu)
        {
            _pdu = pdu;
        }
        public ulong step
        {
            get => _pdu.GetData<ulong>("step");
            set => _pdu.SetData("step", value);
        }
        private Twist _cmd_vel;
        public Twist cmd_vel
        {
            get
            {
                if (_cmd_vel == null)
                {
                    _cmd_vel = new Twist(_pdu.GetData<IPdu>("cmd_vel"));
                }
                return _cmd_vel;
            }
            set
            {
                _cmd_vel = value;
                _pdu.SetData("cmd_vel", value.GetPdu());
            }
        }
        public string animation
        {
            get => _pdu.GetData<string>("animation");
            set => _pdu.SetData("animation", value);
        }
        public string ride
        {
            get => _pdu.GetData<string>("ride");
            set => _pdu.SetData("ride", value);
        }
    }
}
