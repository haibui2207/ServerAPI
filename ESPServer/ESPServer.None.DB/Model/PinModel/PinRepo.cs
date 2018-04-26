using System;
using System.Collections.Generic;

namespace ESPServer_None_DB.Models
{
    public class PinRepo : IPinRepo
    {
        private List<Pin> listData = new List<Pin>();

        public PinRepo()
        {
            Add(new Pin(1, 0));
            Add(new Pin(2, 0));
            Add(new Pin(3, 0));
            Add(new Pin(4, 0));
            Add(new Pin(5, 0));
            Add(new Pin(6, 0));
            Add(new Pin(7, 0));
            Add(new Pin(8, 0));
            Add(new Pin(9, 0));
            Add(new Pin(10, 0));
            Add(new Pin(11, 0));
            Add(new Pin(12, 0));
            Add(new Pin(13, 0));
            Add(new Pin(14, 0));
            Add(new Pin(15, 0));
            Add(new Pin(16, 0));
            Add(new Pin(17, 0));
            Add(new Pin(18, 0));
            Add(new Pin(19, 0));
            Add(new Pin(20, 0));

        }

        public IEnumerable<Pin> GetAll()
        {
            return listData.ToArray();
        }

        public Pin Add(Pin data)
        {
            listData.Add(data);
            return data;
        }

        public Pin ChangData(Pin data)
        {
            foreach (var item in listData)
            {
                if (item.pin == data.pin) item.state = data.state; 
            }
            return data;
        }

        public bool ResetAllPin()
        {
            try
            {
                foreach (var item in listData)
                {
                    item.state = 0;
                }
                return true;
            }
            catch(Exception e)
            {
                return false;
            }
        }

        public Pin GetDataByPin(int pin)
        {
            foreach (var item in listData)
            {
                if (item.pin == pin)
                    return item;
            }
            return null;
        }
    }
}
