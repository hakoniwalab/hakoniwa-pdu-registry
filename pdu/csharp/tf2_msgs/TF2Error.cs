using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.tf2_msgs
{
    public class TF2Error
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public TF2Error(IPdu pdu)
        {
            _pdu = pdu;
        }
        public byte error
        {
            get => _pdu.GetData<byte>("error");
            set => _pdu.SetData("error", value);
        }
        public string error_string
        {
            get => _pdu.GetData<string>("error_string");
            set => _pdu.SetData("error_string", value);
        }
    }
}
