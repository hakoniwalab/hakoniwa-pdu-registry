using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.hako_action_msgs;

namespace hakoniwa.pdu.msgs.sample_action_msgs
{
    public class FibonacciActionFeedback
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public FibonacciActionFeedback(IPdu pdu)
        {
            _pdu = pdu;
        }
        private ActionFeedbackHeader _header;
        public ActionFeedbackHeader header
        {
            get
            {
                if (_header == null)
                {
                    _header = new ActionFeedbackHeader(_pdu.GetData<IPdu>("header"));
                }
                return _header;
            }
            set
            {
                _header = value;
                _pdu.SetData("header", value.GetPdu());
            }
        }
        private FibonacciFeedback _body;
        public FibonacciFeedback body
        {
            get
            {
                if (_body == null)
                {
                    _body = new FibonacciFeedback(_pdu.GetData<IPdu>("body"));
                }
                return _body;
            }
            set
            {
                _body = value;
                _pdu.SetData("body", value.GetPdu());
            }
        }
    }
}
