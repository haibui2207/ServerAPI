using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ServerAPI.Models.MovieModel
{
    public class Movie
    {
        public int id { get; set; }
        public string name { get; set; }
        public int releaseYear { get; set; }

        public Movie(string name, int releaseYear)
        {
            this.name = name;
            this.releaseYear = releaseYear;
        }
    }
}
