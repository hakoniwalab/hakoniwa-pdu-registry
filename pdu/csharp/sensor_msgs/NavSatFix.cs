using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.sensor_msgs
{
    public class NavSatFix
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public NavSatFix(IPdu pdu)
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
        private NavSatStatus _status;
        public NavSatStatus status
        {
            get
            {
                if (_status == null)
                {
                    _status = new NavSatStatus(_pdu.GetData<IPdu>("status"));
                }
                return _status;
            }
            set
            {
                _status = value;
                _pdu.SetData("status", value.GetPdu());
            }
        }
        public double latitude
        {
            get => _pdu.GetData<double>("latitude");
            set => _pdu.SetData("latitude", value);
        }
        public double longitude
        {
            get => _pdu.GetData<double>("longitude");
            set => _pdu.SetData("longitude", value);
        }
        public double altitude
        {
            get => _pdu.GetData<double>("altitude");
            set => _pdu.SetData("altitude", value);
        }
        public double[] position_covariance
        {
            get => _pdu.GetDataArray<double>("position_covariance");
            set => _pdu.SetData("position_covariance", value);
        }
        public byte position_covariance_type
        {
            get => _pdu.GetData<byte>("position_covariance_type");
            set => _pdu.SetData("position_covariance_type", value);
        }
    }
}
