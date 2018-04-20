using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace ServerAPI.Models.UserModel
{
    public class User
    {
        public int id { get; set; }
        [Required]
        [MaxLength(20)]
        public string name { get; set; }
        [Required]
        [MaxLength(8)]
        public string RFID { get; set; }

        public User() { }

        public User(string name , string RFID)
        {
            this.name = name;
            this.RFID = RFID;
        }
    }
}
