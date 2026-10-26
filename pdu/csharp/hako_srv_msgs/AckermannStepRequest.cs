using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.ackermann_msgs;

namespace hakoniwa.pdu.msgs.hako_srv_msgs
{
    public class AckermannStepRequest
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public AckermannStepRequest(IPdu pdu)
        {
            _pdu = pdu;
        }
        public ulong step
        {
            get => _pdu.GetData<ulong>("step");
            set => _pdu.SetData("step", value);
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
