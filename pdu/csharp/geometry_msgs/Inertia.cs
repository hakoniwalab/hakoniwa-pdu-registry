using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using hakoniwa.pdu.interfaces;

namespace hakoniwa.pdu.msgs.geometry_msgs
{
    public class Inertia
    {
        protected internal readonly IPdu _pdu;
        public IPdu GetPdu() { return _pdu; }

        public Inertia(IPdu pdu)
        {
            _pdu = pdu;
        }
        public double m
        {
            get => _pdu.GetData<double>("m");
            set => _pdu.SetData("m", value);
        }
        private Vector3 _com;
        public Vector3 com
        {
            get
            {
                if (_com == null)
                {
                    _com = new Vector3(_pdu.GetData<IPdu>("com"));
                }
                return _com;
            }
            set
            {
                _com = value;
                _pdu.SetData("com", value.GetPdu());
            }
        }
        public double ixx
        {
            get => _pdu.GetData<double>("ixx");
            set => _pdu.SetData("ixx", value);
        }
        public double ixy
        {
            get => _pdu.GetData<double>("ixy");
            set => _pdu.SetData("ixy", value);
        }
        public double ixz
        {
            get => _pdu.GetData<double>("ixz");
            set => _pdu.SetData("ixz", value);
        }
        public double iyy
        {
            get => _pdu.GetData<double>("iyy");
            set => _pdu.SetData("iyy", value);
        }
        public double iyz
        {
            get => _pdu.GetData<double>("iyz");
            set => _pdu.SetData("iyz", value);
        }
        public double izz
        {
            get => _pdu.GetData<double>("izz");
            set => _pdu.SetData("izz", value);
        }
    }
}
