﻿using System.Collections.Generic;

namespace ESPServer.None.DB.Models
{
    interface IPinRepo
    {
        IEnumerable<Pin> GetAll();
        Pin Add(Pin dt);
        Pin ChangData(Pin dt);
        Pin GetDataByPin(int pin);
        bool ResetAllPin();
    }
}