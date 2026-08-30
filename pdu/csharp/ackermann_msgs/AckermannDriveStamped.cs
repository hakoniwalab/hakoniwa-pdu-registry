using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.ackermann_msgs
{
    public class AckermannDriveStamped
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public AckermannDriveStamped(IPdu pdu)
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
        private AckermannDrive _drive;
        public AckermannDrive drive
        {
            get
            {
                if (_drive == null)
                {
                    _drive = new AckermannDrive(_pdu.GetData<IPdu>("drive"));
                }
                return _drive;
            }
            set
            {
                _drive = value;
                _pdu.SetData("drive", value.GetPdu());
            }
        }
    }
}
