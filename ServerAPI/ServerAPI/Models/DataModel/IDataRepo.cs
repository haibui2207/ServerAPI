using System.Collections.Generic;

namespace ServerAPI.Models
{
    interface IDataRepo
    {
        IEnumerable<Data> GetAll();
        Data Add(Data dt);
        Data ChangData(Data dt);
        Data GetDataByPin(int pin);
    }
}
