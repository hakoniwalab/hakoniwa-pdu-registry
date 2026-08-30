using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.ackermann_msgs
{
    public class AckermannDrive
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public AckermannDrive(IPdu pdu)
        {
            _pdu = pdu;
        }
        public float steering_angle
        {
            get => _pdu.GetData<float>("steering_angle");
            set => _pdu.SetData("steering_angle", value);
        }
        public float steering_angle_velocity
        {
            get => _pdu.GetData<float>("steering_angle_velocity");
            set => _pdu.SetData("steering_angle_velocity", value);
        }
        public float speed
        {
            get => _pdu.GetData<float>("speed");
            set => _pdu.SetData("speed", value);
        }
        public float acceleration
        {
            get => _pdu.GetData<float>("acceleration");
            set => _pdu.SetData("acceleration", value);
        }
        public float jerk
        {
            get => _pdu.GetData<float>("jerk");
            set => _pdu.SetData("jerk", value);
        }
    }
}
