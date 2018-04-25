using System.ComponentModel.DataAnnotations;

namespace ESPServer_with_SQL_Server.Models.UserModel
{
    public class User
    {
        public int id { get; set; }
        [Required]
        [MaxLength(20)]
        public string name { get; set; }
        [Required]
        [StringLength(8)]
        public string RFID { get; set; }

        public User() { }

        public User(string name , string RFID)
        {
            this.name = name;
            this.RFID = RFID;
        }
    }
}
