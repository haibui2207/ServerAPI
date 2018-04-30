using System.Threading.Tasks;

namespace ESPServer.Sqlite.Models.UserModel
{
    interface IUserRepo
    {
        Task<User> Add(User dt);
        User Remove(User dt);
        User GetDataByRFID(string RFID);
    }
}
