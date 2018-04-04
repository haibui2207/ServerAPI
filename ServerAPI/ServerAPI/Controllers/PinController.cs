using System;
using Microsoft.AspNetCore.Mvc;
using ServerAPI.Models;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace ServerAPI.Controllers
{
    [Produces("application/json")]
    [Route("api/pin")]
    public class PinController : Controller
    {
        static readonly IDataRepo repository = new DataRepo();

        // GET: api/pin        
        [HttpGet]
        public IActionResult Get()
        {
            var data = repository.GetAll();

            return Ok(data);
        }

        // GET api/pin/{pin}
        [HttpGet("{pin}")]
        public IActionResult Get(int pin)
        {
            try
            {
                if (pin > 0 && pin <= 20)
                {
                    try
                    {
                        return Ok(repository.GetDataByPin(pin));
                    }
                    catch (Exception e)
                    {
                        return NotFound();
                    }
                }
                else
                {
                    return NotFound();
                }
            }
            catch (Exception e)
            {
                return NotFound();
            }
        }

        // POST api/pin
        [HttpPost]
        public IActionResult Post([FromBody] Data dt)
        {
            try
            {
                if (dt == null)
                {
                    return BadRequest();
                }

                if (!ModelState.IsValid)
                {
                    return BadRequest();
                }

                return Ok(repository.ChangData(dt));
            }
            catch (Exception e)
            {
                return BadRequest();
            }
        }

    }
}
