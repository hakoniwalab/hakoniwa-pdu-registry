using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.geometry_msgs;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.sensor_msgs
{
    public class MultiDOFJointState
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public MultiDOFJointState(IPdu pdu)
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
        private Twist[] _twist;
        public Twist[] twist
        {
            get
            {
                if (_twist == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("twist");
                    _twist = new Twist[fieldPdus.Length];
                    Twist[] result = new Twist[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _twist[i] = new Twist(fieldPdus[i]);
                    }
                }
                return _twist;
            }
            set
            {
                _twist = new Twist[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _twist[i] = value[i];
                }
                _pdu.SetData("twist", fieldPdus);
            }
        }
        private Wrench[] _wrench;
        public Wrench[] wrench
        {
            get
            {
                if (_wrench == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("wrench");
                    _wrench = new Wrench[fieldPdus.Length];
                    Wrench[] result = new Wrench[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _wrench[i] = new Wrench(fieldPdus[i]);
                    }
                }
                return _wrench;
            }
            set
            {
                _wrench = new Wrench[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _wrench[i] = value[i];
                }
                _pdu.SetData("wrench", fieldPdus);
            }
        }
    }
}
