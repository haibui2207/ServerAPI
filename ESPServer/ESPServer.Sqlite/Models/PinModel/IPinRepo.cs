using System.Collections.Generic;
using System.Threading.Tasks;

namespace ESPServer.Sqlite.Models
{
    interface IPinRepo
    {
        IEnumerable<Pin> GetAll();
        Task<Pin> Add(Pin dt);
        Task<Pin> ChangData(Pin dt);
        Pin GetDataByPin(int pin);
        Task<bool> ResetAllPin();
    }
}
