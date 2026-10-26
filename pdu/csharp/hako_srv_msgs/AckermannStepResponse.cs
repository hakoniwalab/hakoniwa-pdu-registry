using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.geometry_msgs;

namespace hakoniwa.pdu.msgs.hako_srv_msgs
{
    public class AckermannStepResponse
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public AckermannStepResponse(IPdu pdu)
        {
            _pdu = pdu;
        }
        public ulong step
        {
            get => _pdu.GetData<ulong>("step");
            set => _pdu.SetData("step", value);
        }
        public uint result_code
        {
            get => _pdu.GetData<uint>("result_code");
            set => _pdu.SetData("result_code", value);
        }
        public ulong sim_time_usec
        {
            get => _pdu.GetData<ulong>("sim_time_usec");
            set => _pdu.SetData("sim_time_usec", value);
        }
        private Transform _pose;
        public Transform pose
        {
            get
            {
                if (_pose == null)
                {
                    _pose = new Transform(_pdu.GetData<IPdu>("pose"));
                }
                return _pose;
            }
            set
            {
                _pose = value;
                _pdu.SetData("pose", value.GetPdu());
            }
        }
        private Twist _twist;
        public Twist twist
        {
            get
            {
                if (_twist == null)
                {
                    _twist = new Twist(_pdu.GetData<IPdu>("twist"));
                }
                return _twist;
            }
            set
            {
                _twist = value;
                _pdu.SetData("twist", value.GetPdu());
            }
        }
    }
}
