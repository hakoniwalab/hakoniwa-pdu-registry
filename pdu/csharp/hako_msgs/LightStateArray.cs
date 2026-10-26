using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_msgs
{
    public class LightStateArray
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public LightStateArray(IPdu pdu)
        {
            _pdu = pdu;
        }
        public ulong stamp_usec
        {
            get => _pdu.GetData<ulong>("stamp_usec");
            set => _pdu.SetData("stamp_usec", value);
        }
        public string carrier
        {
            get => _pdu.GetData<string>("carrier");
            set => _pdu.SetData("carrier", value);
        }
        private LightState[] _lights;
        public LightState[] lights
        {
            get
            {
                if (_lights == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("lights");
                    _lights = new LightState[fieldPdus.Length];
                    LightState[] result = new LightState[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _lights[i] = new LightState(fieldPdus[i]);
                    }
                }
                return _lights;
            }
            set
            {
                _lights = new LightState[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _lights[i] = value[i];
                }
                _pdu.SetData("lights", fieldPdus);
            }
        }
    }
}
