using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.geometry_msgs;

namespace hakoniwa.pdu.msgs.hako_srv_msgs
{
    public class RenderObject
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public RenderObject(IPdu pdu)
        {
            _pdu = pdu;
        }
        public string name
        {
            get => _pdu.GetData<string>("name");
            set => _pdu.SetData("name", value);
        }
        public string model
        {
            get => _pdu.GetData<string>("model");
            set => _pdu.SetData("model", value);
        }
        private Pose _pose;
        public Pose pose
        {
            get
            {
                if (_pose == null)
                {
                    _pose = new Pose(_pdu.GetData<IPdu>("pose"));
                }
                return _pose;
            }
            set
            {
                _pose = value;
                _pdu.SetData("pose", value.GetPdu());
            }
        }
    }
}
