using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.geometry_msgs;

namespace hakoniwa.pdu.msgs.trajectory_msgs
{
    public class MultiDOFJointTrajectoryPoint
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public MultiDOFJointTrajectoryPoint(IPdu pdu)
        {
            _pdu = pdu;
        }
        private Transform[] _transforms;
        public Transform[] transforms
        {
            get
            {
                if (_transforms == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("transforms");
                    _transforms = new Transform[fieldPdus.Length];
                    Transform[] result = new Transform[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _transforms[i] = new Transform(fieldPdus[i]);
                    }
                }
                return _transforms;
            }
            set
            {
                _transforms = new Transform[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _transforms[i] = value[i];
                }
                _pdu.SetData("transforms", fieldPdus);
            }
        }
        private Twist[] _velocities;
        public Twist[] velocities
        {
            get
            {
                if (_velocities == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("velocities");
                    _velocities = new Twist[fieldPdus.Length];
                    Twist[] result = new Twist[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _velocities[i] = new Twist(fieldPdus[i]);
                    }
                }
                return _velocities;
            }
            set
            {
                _velocities = new Twist[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _velocities[i] = value[i];
                }
                _pdu.SetData("velocities", fieldPdus);
            }
        }
        private Twist[] _accelerations;
        public Twist[] accelerations
        {
            get
            {
                if (_accelerations == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("accelerations");
                    _accelerations = new Twist[fieldPdus.Length];
                    Twist[] result = new Twist[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _accelerations[i] = new Twist(fieldPdus[i]);
                    }
                }
                return _accelerations;
            }
            set
            {
                _accelerations = new Twist[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _accelerations[i] = value[i];
                }
                _pdu.SetData("accelerations", fieldPdus);
            }
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
