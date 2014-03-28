using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace TT_FFX_Butterfly
{
    class DirectionPoint
    {
        //Same value for C++ program
        public enum ARROW
        {
            NOPE = 0,
            UP = 1,
            DOWN = 2,
            LEFT = 4,
            RIGHT = 8,
            //Just In case maybe the are needed
            MIDDLE_UP = 16,
            MIDDLE_DOWN = 32,
            MIDDLE_LEFT = 64,
            MIDDLE_RIGHT = 128
        };

        public bool isButteFly { get; set; }
        public ARROW point { get; set; }
        public Vector position { get; set; }
    }
}
