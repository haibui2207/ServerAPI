using System.Threading.Tasks;

namespace ESPServer_with_SQL_Server.Models.UserModel
{
    interface IUserRepo
    {
        Task<User> Add(User dt);
        User Remove(User dt);
        User GetDataByRFID(string RFID);
    }
}
