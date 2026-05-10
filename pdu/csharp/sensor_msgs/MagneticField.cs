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
    public class MagneticField
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public MagneticField(IPdu pdu)
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
        private Vector3 _magnetic_field;
        public Vector3 magnetic_field
        {
            get
            {
                if (_magnetic_field == null)
                {
                    _magnetic_field = new Vector3(_pdu.GetData<IPdu>("magnetic_field"));
                }
                return _magnetic_field;
            }
            set
            {
                _magnetic_field = value;
                _pdu.SetData("magnetic_field", value.GetPdu());
            }
        }
        public double[] magnetic_field_covariance
        {
            get => _pdu.GetDataArray<double>("magnetic_field_covariance");
            set => _pdu.SetData("magnetic_field_covariance", value);
        }
    }
}
