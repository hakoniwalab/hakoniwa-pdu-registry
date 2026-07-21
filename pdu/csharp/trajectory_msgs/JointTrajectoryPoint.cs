using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;

namespace hakoniwa.pdu.msgs.trajectory_msgs
{
    public class JointTrajectoryPoint
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public JointTrajectoryPoint(IPdu pdu)
        {
            _pdu = pdu;
        }
        public double[] positions
        {
            get => _pdu.GetDataArray<double>("positions");
            set => _pdu.SetData("positions", value);
        }
        public double[] velocities
        {
            get => _pdu.GetDataArray<double>("velocities");
            set => _pdu.SetData("velocities", value);
        }
        public double[] accelerations
        {
            get => _pdu.GetDataArray<double>("accelerations");
            set => _pdu.SetData("accelerations", value);
        }
        public double[] effort
        {
            get => _pdu.GetDataArray<double>("effort");
            set => _pdu.SetData("effort", value);
        }
        private Duration _time_from_start;
        public Duration time_from_start
        {
            get
            {
                if (_time_from_start == null)
                {
                    _time_from_start = new Duration(_pdu.GetData<IPdu>("time_from_start"));
                }
                return _time_from_start;
            }
            set
            {
                _time_from_start = value;
                _pdu.SetData("time_from_start", value.GetPdu());
            }
        }
    }
}
