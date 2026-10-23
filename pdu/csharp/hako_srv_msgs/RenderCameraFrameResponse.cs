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
    public class RenderCameraFrameResponse
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public RenderCameraFrameResponse(IPdu pdu)
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
        private Image _rgb;
        public Image rgb
        {
            get
            {
                if (_rgb == null)
                {
                    _rgb = new Image(_pdu.GetData<IPdu>("rgb"));
                }
                return _rgb;
            }
            set
            {
                _rgb = value;
                _pdu.SetData("rgb", value.GetPdu());
            }
        }
        private Image _depth;
        public Image depth
        {
            get
            {
                if (_depth == null)
                {
                    _depth = new Image(_pdu.GetData<IPdu>("depth"));
                }
                return _depth;
            }
            set
            {
                _depth = value;
                _pdu.SetData("depth", value.GetPdu());
            }
        }
        private Image _segmentation;
        public Image segmentation
        {
            get
            {
                if (_segmentation == null)
                {
                    _segmentation = new Image(_pdu.GetData<IPdu>("segmentation"));
                }
                return _segmentation;
            }
            set
            {
                _segmentation = value;
                _pdu.SetData("segmentation", value.GetPdu());
            }
        }
    }
}
