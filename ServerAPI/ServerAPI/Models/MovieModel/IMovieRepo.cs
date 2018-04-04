using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ServerAPI.Models.MovieModel
{
    interface IMovieRepo
    {
        IEnumerable<Movie> GetAll();
        Movie Add(Movie dt);
        Movie GetDataByIndex(int index);
        IEnumerable<Movie> GetDataByName(string name);
    }
}
