using System;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using ServerAPI.DataContext;
using ServerAPI.Models;

//For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace ServerAPI.Controllers
{
    [Produces("application/json")]
    [Route("api/pin")]
    public class PinController : Controller
    {
        private readonly IDataRepo _repository;

        public PinController(ServerAPIContext context)
        {
            this._repository = new DataRepo(context);
        }

        //GET: api/pin
       [HttpGet]
        public IActionResult Get()
        {
            var data = _repository.GetAll();

            return Ok(data);
        }

        // GET api/pin/{pin}
        [HttpGet("{pin}")]
        public IActionResult Get(int pin)
        {
            try
            {
                if (ModelState.IsValid)
                {
                    return Ok(_repository.GetDataByPin(pin));
                }
                else
                {
                    return BadRequest(ModelState);
                }
            }
            catch (Exception e)
            {
                return NotFound();
            }
        }

        // POST api/pin
        [HttpPost]
        public async Task<IActionResult> Post([FromBody] Data dt)
        {
            try
            {
                if (dt == null)
                {
                    return BadRequest(ModelState);
                }

                if (!ModelState.IsValid)
                {
                    return BadRequest(ModelState);
                }

                var data = await _repository.ChangData(dt);

                return Ok(data);
            }
            catch (Exception e)
            {
                return BadRequest();
            }
        }

        [HttpPost]
        [Route("ResetAllPin")]
        public async Task<IActionResult> ResetAllPin()
        {
            try
            {
                bool check = await _repository.ResetAllPin();
                if (check) return Ok("Reset all pin success!");
                else return BadRequest("Error reset all pin");

            }
            catch (Exception e)
            {
                return BadRequest();
            }
        }

    }
}
