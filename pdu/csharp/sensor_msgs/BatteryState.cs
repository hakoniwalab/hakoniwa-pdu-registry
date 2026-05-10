using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;
using hakoniwa.pdu.msgs.builtin_interfaces;
using hakoniwa.pdu.msgs.std_msgs;

namespace hakoniwa.pdu.msgs.sensor_msgs
{
    public class BatteryState
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public BatteryState(IPdu pdu)
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
        public float voltage
        {
            get => _pdu.GetData<float>("voltage");
            set => _pdu.SetData("voltage", value);
        }
        public float temperature
        {
            get => _pdu.GetData<float>("temperature");
            set => _pdu.SetData("temperature", value);
        }
        public float current
        {
            get => _pdu.GetData<float>("current");
            set => _pdu.SetData("current", value);
        }
        public float charge
        {
            get => _pdu.GetData<float>("charge");
            set => _pdu.SetData("charge", value);
        }
        public float capacity
        {
            get => _pdu.GetData<float>("capacity");
            set => _pdu.SetData("capacity", value);
        }
        public float design_capacity
        {
            get => _pdu.GetData<float>("design_capacity");
            set => _pdu.SetData("design_capacity", value);
        }
        public float percentage
        {
            get => _pdu.GetData<float>("percentage");
            set => _pdu.SetData("percentage", value);
        }
        public byte power_supply_status
        {
            get => _pdu.GetData<byte>("power_supply_status");
            set => _pdu.SetData("power_supply_status", value);
        }
        public byte power_supply_health
        {
            get => _pdu.GetData<byte>("power_supply_health");
            set => _pdu.SetData("power_supply_health", value);
        }
        public byte power_supply_technology
        {
            get => _pdu.GetData<byte>("power_supply_technology");
            set => _pdu.SetData("power_supply_technology", value);
        }
        public bool present
        {
            get => _pdu.GetData<bool>("present");
            set => _pdu.SetData("present", value);
        }
        public float[] cell_voltage
        {
            get => _pdu.GetDataArray<float>("cell_voltage");
            set => _pdu.SetData("cell_voltage", value);
        }
        public float[] cell_temperature
        {
            get => _pdu.GetDataArray<float>("cell_temperature");
            set => _pdu.SetData("cell_temperature", value);
        }
        public string location
        {
            get => _pdu.GetData<string>("location");
            set => _pdu.SetData("location", value);
        }
        public string serial_number
        {
            get => _pdu.GetData<string>("serial_number");
            set => _pdu.SetData("serial_number", value);
        }
    }
}
