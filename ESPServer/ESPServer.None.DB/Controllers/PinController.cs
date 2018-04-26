using System;
using ESPServer_None_DB.Models;
using Microsoft.AspNetCore.Mvc;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace ESPServer_None_DB.Controllers
{
    [Produces("application/json")]
    [Route("api/pin")]
    public class PinController : Controller
    {
        static readonly IPinRepo repository = new PinRepo();

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
        public IActionResult Post([FromBody] Pin dt)
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

        [HttpPost]
        [Route("ResetAllPin")]
        public IActionResult ResetAllPin()
        {
            try
            {
                bool check = repository.ResetAllPin();
                if(check) return Ok("Reset all pin success!");
                else return BadRequest("Error reset all pin");

            }
            catch (Exception e)
            {
                return BadRequest();
            }
        }

    }
}
