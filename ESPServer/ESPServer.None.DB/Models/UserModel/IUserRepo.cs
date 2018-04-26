namespace ESPServer.None.DB.Models.UserModel
{
    interface IUserRepo
    {
        User Add(User dt);
        User Remove(User dt);
        User GetDataByRFID(string RFID);
    }
}
