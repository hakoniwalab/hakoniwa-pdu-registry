using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.trajectory_msgs
{
    public class JointTrajectory
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public JointTrajectory(IPdu pdu)
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
        public string[] joint_names
        {
            get => _pdu.GetDataArray<string>("joint_names");
            set => _pdu.SetData("joint_names", value);
        }
        private JointTrajectoryPoint[] _points;
        public JointTrajectoryPoint[] points
        {
            get
            {
                if (_points == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("points");
                    _points = new JointTrajectoryPoint[fieldPdus.Length];
                    JointTrajectoryPoint[] result = new JointTrajectoryPoint[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _points[i] = new JointTrajectoryPoint(fieldPdus[i]);
                    }
                }
                return _points;
            }
            set
            {
                _points = new JointTrajectoryPoint[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _points[i] = value[i];
                }
                _pdu.SetData("points", fieldPdus);
            }
        }
    }
}
