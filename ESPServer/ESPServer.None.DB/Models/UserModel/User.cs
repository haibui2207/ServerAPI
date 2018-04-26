namespace ESPServer.None.DB.Models.UserModel
{
    public class User
    {
        public int id { get; set; }
        public string name { get; set; }
        public string RFID { get; set; }

        public User(string name , string RFID)
        {
            this.name = name;
            this.RFID = RFID;
        }
    }
}
