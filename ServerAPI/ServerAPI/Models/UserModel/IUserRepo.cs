namespace ServerAPI.Models.UserModel
{
    interface IUserRepo
    {
        bool Add(User dt);
        bool Remove(User dt);
        User GetDataByRFID(string RFID);
    }
}
