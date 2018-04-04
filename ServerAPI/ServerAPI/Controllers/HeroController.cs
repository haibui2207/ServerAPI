using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using ServerAPI.Models.HeroModel;

namespace ServerAPI.Controllers
{
    [Produces("application/json")]
    [Route("api/Hero")]
    public class HeroController : Controller
    {
        static readonly IHeroRepo repository = new HeroRepo();

        // GET: api/Hero        
        [HttpGet]
        public IActionResult Get()
        {
            var data = repository.GetAll();

            return Ok(data);
        }

        // GET api/Hero/{index}
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