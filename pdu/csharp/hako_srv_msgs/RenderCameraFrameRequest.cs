using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.geometry_msgs;

namespace hakoniwa.pdu.msgs.hako_srv_msgs
{
    public class RenderCameraFrameRequest
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public RenderCameraFrameRequest(IPdu pdu)
        {
            _pdu = pdu;
        }
        public string camera_name
        {
            get => _pdu.GetData<string>("camera_name");
            set => _pdu.SetData("camera_name", value);
        }
        public ulong sim_time_usec
        {
            get => _pdu.GetData<ulong>("sim_time_usec");
            set => _pdu.SetData("sim_time_usec", value);
        }
        private Pose _camera_pose;
        public Pose camera_pose
        {
            get
            {
                if (_camera_pose == null)
                {
                    _camera_pose = new Pose(_pdu.GetData<IPdu>("camera_pose"));
                }
                return _camera_pose;
            }
            set
            {
                _camera_pose = value;
                _pdu.SetData("camera_pose", value.GetPdu());
            }
        }
        public byte outputs
        {
            get => _pdu.GetData<byte>("outputs");
            set => _pdu.SetData("outputs", value);
        }
    }
}
