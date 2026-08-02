using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.hako_action_msgs;

namespace hakoniwa.pdu.msgs.sample_action_msgs
{
    public class FibonacciActionResponse
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public FibonacciActionResponse(IPdu pdu)
        {
            _pdu = pdu;
        }
        private ActionResponseHeader _header;
        public ActionResponseHeader header
        {
            get
            {
                if (_header == null)
                {
                    _header = new ActionResponseHeader(_pdu.GetData<IPdu>("header"));
                }
                return _header;
            }
            set
            {
                _header = value;
                _pdu.SetData("header", value.GetPdu());
            }
        }
        private FibonacciResult _body;
        public FibonacciResult body
        {
            get
            {
                if (_body == null)
                {
                    _body = new FibonacciResult(_pdu.GetData<IPdu>("body"));
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
