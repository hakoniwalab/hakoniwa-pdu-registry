using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_msgs
{
    public class DroneVisualState
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public DroneVisualState(IPdu pdu)
        {
            _pdu = pdu;
        }
        public float x
        {
            get => _pdu.GetData<float>("x");
            set => _pdu.SetData("x", value);
        }
        public float y
        {
            get => _pdu.GetData<float>("y");
            set => _pdu.SetData("y", value);
        }
        public float z
        {
            get => _pdu.GetData<float>("z");
            set => _pdu.SetData("z", value);
        }
        public float roll
        {
            get => _pdu.GetData<float>("roll");
            set => _pdu.SetData("roll", value);
        }
        public float pitch
        {
            get => _pdu.GetData<float>("pitch");
            set => _pdu.SetData("pitch", value);
        }
        public float yaw
        {
            get => _pdu.GetData<float>("yaw");
            set => _pdu.SetData("yaw", value);
        }
        public float[] pwm_duty
        {
            get => _pdu.GetDataArray<float>("pwm_duty");
            set => _pdu.SetData("pwm_duty", value);
        }
    }
}
