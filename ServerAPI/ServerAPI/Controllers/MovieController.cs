using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using ServerAPI.Models;
using ServerAPI.Models.MovieModel;

namespace ServerAPI.Controllers
{
    [Produces("application/json")]
    [Route("api/Movie")]
    public class MovieController : Controller
    {
        static readonly IMovieRepo repository = new MovieRepo();

        // GET: api/Movie        
        [HttpGet]
        public IActionResult Get()
        {
            var data = repository.GetAll();

            return Ok(data);
        }

        // GET api/Movie/{index}
        [HttpGet("{index}")]
        public IActionResult Get(int index)
        {
            try
            {
                return Ok(repository.GetDataByIndex(index));
            }
            catch (Exception e)
            {
                return NotFound();
            }
        }

    }
}