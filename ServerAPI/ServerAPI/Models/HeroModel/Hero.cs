using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ServerAPI.Models.HeroModel
{
    public class Hero
    {
        public int id { get; set; }
        public string name { get; set; }

        public Hero(string name)
        {
            this.name = name;
        }
    }
}
