using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.geometry_msgs;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.sensor_msgs
{
    public class PointCloud
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public PointCloud(IPdu pdu)
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
        private Point32[] _points;
        public Point32[] points
        {
            get
            {
                if (_points == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("points");
                    _points = new Point32[fieldPdus.Length];
                    Point32[] result = new Point32[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _points[i] = new Point32(fieldPdus[i]);
                    }
                }
                return _points;
            }
            set
            {
                _points = new Point32[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _points[i] = value[i];
                }
                _pdu.SetData("points", fieldPdus);
            }
        }
        private ChannelFloat32[] _channels;
        public ChannelFloat32[] channels
        {
            get
            {
                if (_channels == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("channels");
                    _channels = new ChannelFloat32[fieldPdus.Length];
                    ChannelFloat32[] result = new ChannelFloat32[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _channels[i] = new ChannelFloat32(fieldPdus[i]);
                    }
                }
                return _channels;
            }
            set
            {
                _channels = new ChannelFloat32[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _channels[i] = value[i];
                }
                _pdu.SetData("channels", fieldPdus);
            }
        }
    }
}
