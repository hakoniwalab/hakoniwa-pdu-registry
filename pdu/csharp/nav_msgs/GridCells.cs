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
    public class GridCells
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public GridCells(IPdu pdu)
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
        public float cell_width
        {
            get => _pdu.GetData<float>("cell_width");
            set => _pdu.SetData("cell_width", value);
        }
        public float cell_height
        {
            get => _pdu.GetData<float>("cell_height");
            set => _pdu.SetData("cell_height", value);
        }
        private Point[] _cells;
        public Point[] cells
        {
            get
            {
                if (_cells == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("cells");
                    _cells = new Point[fieldPdus.Length];
                    Point[] result = new Point[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _cells[i] = new Point(fieldPdus[i]);
                    }
                }
                return _cells;
            }
            set
            {
                _cells = new Point[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _cells[i] = value[i];
                }
                _pdu.SetData("cells", fieldPdus);
            }
        }
    }
}
