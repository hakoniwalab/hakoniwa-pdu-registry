using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.sample_action_msgs
{
    public class FibonacciGoal
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public FibonacciGoal(IPdu pdu)
        {
            _pdu = pdu;
        }
        public int order
        {
            get => _pdu.GetData<int>("order");
            set => _pdu.SetData("order", value);
        }
    }
}
