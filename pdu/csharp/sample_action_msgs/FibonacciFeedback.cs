using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.sample_action_msgs
{
    public class FibonacciFeedback
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public FibonacciFeedback(IPdu pdu)
        {
            _pdu = pdu;
        }
        public int[] partial_sequence
        {
            get => _pdu.GetDataArray<int>("partial_sequence");
            set => _pdu.SetData("partial_sequence", value);
        }
    }
}
