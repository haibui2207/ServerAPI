using System.Collections.Generic;

namespace ServerAPI.Models.HeroModel
{
    public class HeroRepo : IHeroRepo
    {
        private List<Hero> listHeros = new List<Hero>();
        private int _nextID = 1;

        public HeroRepo()
        {
            Add(new Hero("Mr. Nice"));
            Add(new Hero("Narco"));
            Add(new Hero("Bombasto"));
            Add(new Hero("Celeritas"));
            Add(new Hero("Magneta"));
            Add(new Hero("RubberMan"));
            Add(new Hero("Dynama"));
            Add(new Hero("Dr IQ"));
            Add(new Hero("Magma"));
            Add(new Hero("Tornado"));
        }

        public IEnumerable<Hero> GetAll()
        {
            return listHeros.ToArray();
        }

        public Hero Add(Hero newHero)
        {
            newHero.id = _nextID;
            _nextID++;
            listHeros.Add(newHero);
            return newHero;
        }

        public Hero GetDataByIndex(int index)
        {
            foreach (var item in listHeros)
            {
                if (item.id == index)
                    return item;
            }
            return null;
        }

        public IEnumerable<Hero> GetDataByName(string name)
        {
            List<Hero> list = new List<Hero>();
            foreach (var item in listHeros)
            {
                if (item.name == name)
                    list.Add(item);
            }
            return list;
        }
    }
}
