using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.geometry_msgs
{
    public class Wrench
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public Wrench(IPdu pdu)
        {
            _pdu = pdu;
        }
        private Vector3 _force;
        public Vector3 force
        {
            get
            {
                if (_force == null)
                {
                    _force = new Vector3(_pdu.GetData<IPdu>("force"));
                }
                return _force;
            }
            set
            {
                _force = value;
                _pdu.SetData("force", value.GetPdu());
            }
        }
        private Vector3 _torque;
        public Vector3 torque
        {
            get
            {
                if (_torque == null)
                {
                    _torque = new Vector3(_pdu.GetData<IPdu>("torque"));
                }
                return _torque;
            }
            set
            {
                _torque = value;
                _pdu.SetData("torque", value.GetPdu());
            }
        }
    }
}
