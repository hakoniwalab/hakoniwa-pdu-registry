using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.geometry_msgs;

namespace hakoniwa.pdu.msgs.nav_msgs
{
    public class MapMetaData
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public MapMetaData(IPdu pdu)
        {
            _pdu = pdu;
        }
        private Time _map_load_time;
        public Time map_load_time
        {
            get
            {
                if (_map_load_time == null)
                {
                    _map_load_time = new Time(_pdu.GetData<IPdu>("map_load_time"));
                }
                return _map_load_time;
            }
            set
            {
                _map_load_time = value;
                _pdu.SetData("map_load_time", value.GetPdu());
            }
        }
        public float resolution
        {
            get => _pdu.GetData<float>("resolution");
            set => _pdu.SetData("resolution", value);
        }
        public uint width
        {
            get => _pdu.GetData<uint>("width");
            set => _pdu.SetData("width", value);
        }
        public uint height
        {
            get => _pdu.GetData<uint>("height");
            set => _pdu.SetData("height", value);
        }
        private Pose _origin;
        public Pose origin
        {
            get
            {
                if (_origin == null)
                {
                    _origin = new Pose(_pdu.GetData<IPdu>("origin"));
                }
                return _origin;
            }
            set
            {
                _origin = value;
                _pdu.SetData("origin", value.GetPdu());
            }
        }
    }
}
