using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ServerAPI.Models.MovieModel
{
    public class MovieRepo : IMovieRepo
    {
        private List<Movie> listMovies = new List<Movie>();
        private int _nextID = 1;

        public MovieRepo()
        {
            Add(new Movie("The Ghost and the Darkness", 1996));
            Add(new Movie("The Blind Side", 2009));
            Add(new Movie("Star Wars", 1977));
            Add(new Movie("Back to the Future", 1985));
            Add(new Movie("The Matrix", 1999));
            Add(new Movie("Inception", 2010));
            Add(new Movie("Freedom Writers", 2007));
            Add(new Movie("Appolo 13", 1995));
            Add(new Movie("Lone Survivor", 2013));
            Add(new Movie("All the President's Men", 1976));
            Add(new Movie("Walk the Line", 2005));
        }

        public IEnumerable<Movie> GetAll()
        {
            return listMovies.ToArray();
        }

        public Movie Add(Movie newMovie)
        {
            newMovie.id = _nextID;
            _nextID++;
            listMovies.Add(newMovie);
            return newMovie;
        }

        public Movie GetDataByIndex(int index)
        {
            foreach (var item in listMovies)
            {
                if (item.id == index)
                    return item;
            }
            return null;
        }

        public IEnumerable<Movie> GetDataByName(string name)
        {
            List<Movie> list = new List<Movie>();
            foreach (var item in listMovies)
            {
                if (item.name == name)
                    list.Add(item);
            }
            return list;
        }
    }
}
