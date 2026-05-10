using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.geometry_msgs
{
    public class PoseArray
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public PoseArray(IPdu pdu)
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
        private Pose[] _poses;
        public Pose[] poses
        {
            get
            {
                if (_poses == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("poses");
                    _poses = new Pose[fieldPdus.Length];
                    Pose[] result = new Pose[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _poses[i] = new Pose(fieldPdus[i]);
                    }
                }
                return _poses;
            }
            set
            {
                _poses = new Pose[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _poses[i] = value[i];
                }
                _pdu.SetData("poses", fieldPdus);
            }
        }
    }
}
