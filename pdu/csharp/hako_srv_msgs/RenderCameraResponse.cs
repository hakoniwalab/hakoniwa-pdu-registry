using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.sensor_msgs;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.hako_srv_msgs
{
    public class RenderCameraResponse
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public RenderCameraResponse(IPdu pdu)
        {
            _pdu = pdu;
        }
        public uint result_code
        {
            get => _pdu.GetData<uint>("result_code");
            set => _pdu.SetData("result_code", value);
        }
        public ulong sim_time_usec
        {
            get => _pdu.GetData<ulong>("sim_time_usec");
            set => _pdu.SetData("sim_time_usec", value);
        }
        private Image _image;
        public Image image
        {
            get
            {
                if (_image == null)
                {
                    _image = new Image(_pdu.GetData<IPdu>("image"));
                }
                return _image;
            }
            set
            {
                _image = value;
                _pdu.SetData("image", value.GetPdu());
            }
        }
    }
}
