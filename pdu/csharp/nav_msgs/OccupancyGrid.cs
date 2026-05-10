using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.geometry_msgs;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.nav_msgs
{
    public class OccupancyGrid
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public OccupancyGrid(IPdu pdu)
        {
            _pdu = pdu;
        }
        private Header _header;
        public Header header
        {
            get
            {
                if (_header == null)
                {
                    _header = new Header(_pdu.GetData<IPdu>("header"));
                }
                return _header;
            }
            set
            {
                _header = value;
                _pdu.SetData("header", value.GetPdu());
            }
        }
        private MapMetaData _info;
        public MapMetaData info
        {
            get
            {
                if (_info == null)
                {
                    _info = new MapMetaData(_pdu.GetData<IPdu>("info"));
                }
                return _info;
            }
            set
            {
                _info = value;
                _pdu.SetData("info", value.GetPdu());
            }
        }
        public sbyte[] data
        {
            get => _pdu.GetDataArray<sbyte>("data");
            set => _pdu.SetData("data", value);
        }
    }
}
