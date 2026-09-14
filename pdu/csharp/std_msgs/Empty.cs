using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.std_msgs
{
    public class Empty
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public Empty(IPdu pdu)
        {
            _pdu = pdu;
        }
        public byte hako_dummy
        {
            get => _pdu.GetData<byte>("hako_dummy");
            set => _pdu.SetData("hako_dummy", value);
        }
    }
}
