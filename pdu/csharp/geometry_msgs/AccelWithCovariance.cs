using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.geometry_msgs
{
    public class AccelWithCovariance
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public AccelWithCovariance(IPdu pdu)
        {
            _pdu = pdu;
        }
        private Accel _accel;
        public Accel accel
        {
            get
            {
                if (_accel == null)
                {
                    _accel = new Accel(_pdu.GetData<IPdu>("accel"));
                }
                return _accel;
            }
            set
            {
                _accel = value;
                _pdu.SetData("accel", value.GetPdu());
            }
        }
        public double[] covariance
        {
            get => _pdu.GetDataArray<double>("covariance");
            set => _pdu.SetData("covariance", value);
        }
    }
}
