using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.sensor_msgs
{
    public class MultiEchoLaserScan
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public MultiEchoLaserScan(IPdu pdu)
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
        public float angle_min
        {
            get => _pdu.GetData<float>("angle_min");
            set => _pdu.SetData("angle_min", value);
        }
        public float angle_max
        {
            get => _pdu.GetData<float>("angle_max");
            set => _pdu.SetData("angle_max", value);
        }
        public float angle_increment
        {
            get => _pdu.GetData<float>("angle_increment");
            set => _pdu.SetData("angle_increment", value);
        }
        public float time_increment
        {
            get => _pdu.GetData<float>("time_increment");
            set => _pdu.SetData("time_increment", value);
        }
        public float scan_time
        {
            get => _pdu.GetData<float>("scan_time");
            set => _pdu.SetData("scan_time", value);
        }
        public float range_min
        {
            get => _pdu.GetData<float>("range_min");
            set => _pdu.SetData("range_min", value);
        }
        public float range_max
        {
            get => _pdu.GetData<float>("range_max");
            set => _pdu.SetData("range_max", value);
        }
        private LaserEcho[] _ranges;
        public LaserEcho[] ranges
        {
            get
            {
                if (_ranges == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("ranges");
                    _ranges = new LaserEcho[fieldPdus.Length];
                    LaserEcho[] result = new LaserEcho[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _ranges[i] = new LaserEcho(fieldPdus[i]);
                    }
                }
                return _ranges;
            }
            set
            {
                _ranges = new LaserEcho[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _ranges[i] = value[i];
                }
                _pdu.SetData("ranges", fieldPdus);
            }
        }
        private LaserEcho[] _intensities;
        public LaserEcho[] intensities
        {
            get
            {
                if (_intensities == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("intensities");
                    _intensities = new LaserEcho[fieldPdus.Length];
                    LaserEcho[] result = new LaserEcho[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _intensities[i] = new LaserEcho(fieldPdus[i]);
                    }
                }
                return _intensities;
            }
            set
            {
                _intensities = new LaserEcho[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _intensities[i] = value[i];
                }
                _pdu.SetData("intensities", fieldPdus);
            }
        }
    }
}
