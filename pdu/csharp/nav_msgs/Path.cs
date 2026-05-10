using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.geometry_msgs;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.nav_msgs
{
    public class Path
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public Path(IPdu pdu)
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
        private PoseStamped[] _poses;
        public PoseStamped[] poses
        {
            get
            {
                if (_poses == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("poses");
                    _poses = new PoseStamped[fieldPdus.Length];
                    PoseStamped[] result = new PoseStamped[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _poses[i] = new PoseStamped(fieldPdus[i]);
                    }
                }
                return _poses;
            }
            set
            {
                _poses = new PoseStamped[value.Length];
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
