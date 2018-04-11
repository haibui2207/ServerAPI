using System;
using System.Collections.Generic;

namespace ServerAPI.Models
{
    public class DataRepo : IDataRepo
    {
        private List<Data> listData = new List<Data>();

        public DataRepo()
        {
            Add(new Data(1, 0));
            Add(new Data(2, 0));
            Add(new Data(3, 0));
            Add(new Data(4, 0));
            Add(new Data(5, 0));
            Add(new Data(6, 0));
            Add(new Data(7, 0));
            Add(new Data(8, 0));
            Add(new Data(9, 0));
            Add(new Data(10, 0));
            Add(new Data(11, 0));
            Add(new Data(12, 0));
            Add(new Data(13, 0));
            Add(new Data(14, 0));
            Add(new Data(15, 0));
            Add(new Data(16, 0));
            Add(new Data(17, 0));
            Add(new Data(18, 0));
            Add(new Data(19, 0));
            Add(new Data(20, 0));

        }

        public IEnumerable<Data> GetAll()
        {
            return listData.ToArray();
        }

        public Data Add(Data data)
        {
            listData.Add(data);
            return data;
        }

        public Data ChangData(Data data)
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

        public Data GetDataByPin(int pin)
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
