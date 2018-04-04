using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ServerAPI.Models.HeroModel
{
    interface IHeroRepo
    {
        IEnumerable<Hero> GetAll();
        Hero Add(Hero dt);
        Hero GetDataByIndex(int index);
        IEnumerable<Hero> GetDataByName(string name);
    }
}
