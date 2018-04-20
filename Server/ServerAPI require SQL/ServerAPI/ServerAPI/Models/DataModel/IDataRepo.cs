using System.Collections.Generic;
using System.Threading.Tasks;
using ServerAPI.DataContext;

namespace ServerAPI.Models
{
    interface IDataRepo
    {
        IEnumerable<Data> GetAll();
        Task<Data> Add(Data dt);
        Task<Data> ChangData(Data dt);
        Data GetDataByPin(int pin);
        Task<bool> ResetAllPin();
    }
}
