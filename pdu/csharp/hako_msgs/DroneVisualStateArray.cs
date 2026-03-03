using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.hako_msgs
{
    public class DroneVisualStateArray
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public DroneVisualStateArray(IPdu pdu)
        {
            _pdu = pdu;
        }
        public uint sequence_id
        {
            get => _pdu.GetData<uint>("sequence_id");
            set => _pdu.SetData("sequence_id", value);
        }
        public uint chunk_index
        {
            get => _pdu.GetData<uint>("chunk_index");
            set => _pdu.SetData("chunk_index", value);
        }
        public uint chunk_count
        {
            get => _pdu.GetData<uint>("chunk_count");
            set => _pdu.SetData("chunk_count", value);
        }
        public uint start_index
        {
            get => _pdu.GetData<uint>("start_index");
            set => _pdu.SetData("start_index", value);
        }
        public uint valid_count
        {
            get => _pdu.GetData<uint>("valid_count");
            set => _pdu.SetData("valid_count", value);
        }
        private DroneVisualState[] _drones;
        public DroneVisualState[] drones
        {
            get
            {
                if (_drones == null)
                {
                    var fieldPdus = _pdu.GetDataArray<IPdu>("drones");
                    _drones = new DroneVisualState[fieldPdus.Length];
                    DroneVisualState[] result = new DroneVisualState[fieldPdus.Length];
                    for (int i = 0; i < fieldPdus.Length; i++)
                    {
                        _drones[i] = new DroneVisualState(fieldPdus[i]);
                    }
                }
                return _drones;
            }
            set
            {
                _drones = new DroneVisualState[value.Length];
                IPdu[] fieldPdus = new IPdu[value.Length];
                for (int i = 0; i < value.Length; i++)
                {
                    fieldPdus[i] = value[i].GetPdu();
                    _drones[i] = value[i];
                }
                _pdu.SetData("drones", fieldPdus);
            }
        }
    }
}
