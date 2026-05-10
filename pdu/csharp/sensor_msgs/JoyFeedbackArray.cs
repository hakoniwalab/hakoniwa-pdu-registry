using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.sensor_msgs
{
    public class JoyFeedbackArray
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public JoyFeedbackArray(IPdu pdu)
        {
            _pdu = pdu;
        }
        private JoyFeedback[] _array;
        public JoyFeedback[] array
        {
            get
            {
                if (_array == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("array");
                    _array = new JoyFeedback[fieldPdus.Length];
                    JoyFeedback[] result = new JoyFeedback[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _array[i] = new JoyFeedback(fieldPdus[i]);
                    }
                }
                return _array;
            }
            set
            {
                _array = new JoyFeedback[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _array[i] = value[i];
                }
                _pdu.SetData("array", fieldPdus);
            }
        }
    }
}
