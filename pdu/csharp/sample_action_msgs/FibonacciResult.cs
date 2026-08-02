using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.sample_action_msgs
{
    public class FibonacciResult
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public FibonacciResult(IPdu pdu)
        {
            _pdu = pdu;
        }
        public int[] sequence
        {
            get => _pdu.GetDataArray<int>("sequence");
            set => _pdu.SetData("sequence", value);
        }
    }
}
