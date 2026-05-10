using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.geometry_msgs
{
    public class Polygon
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public Polygon(IPdu pdu)
        {
            _pdu = pdu;
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
    }
}
