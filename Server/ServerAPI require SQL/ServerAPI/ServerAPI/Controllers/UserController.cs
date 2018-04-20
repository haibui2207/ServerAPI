using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using ServerAPI.DataContext;
using ServerAPI.Models.UserModel;

namespace ServerAPI.Controllers
{
    [Produces("application/json")]
    [Route("api/User")]
    public class UserController : Controller
    {
        private readonly IUserRepo _repository;

        public UserController(ServerAPIContext context)
        {
            this._repository = new UserRepo(context);
        }

        // GET api/User/{RFID}
        [HttpGet("{RFID}")]
        public IActionResult Get(string RFID)
        {
            try
            {
                if (!ModelState.IsValid)
                {
                    return BadRequest(ModelState);
                }

                return Ok(_repository.GetDataByRFID(RFID));
            }
            catch (Exception e)
            {
                return NotFound();
            }
        }

        // POST api/User
        [HttpPost]
        public async Task<IActionResult> Post([FromBody] User newUser)
        {
            try
            {
                if (!ModelState.IsValid)
                {
                    return BadRequest(ModelState);
                }

                var data = await _repository.Add(newUser);
                return Ok("Add User Successed.");
            }
            catch (Exception e)
            {
                return BadRequest();
            }
        }

        // POST api/User
        [HttpDelete]
        public IActionResult Delete([FromBody] User deletedUser)
        {
            try
            {
                if (!ModelState.IsValid)
                {
                    return BadRequest(ModelState);
                }

                try
                {
                    var data = _repository.Remove(deletedUser);
                    return Ok(data);
                }
                catch
                {
                    return NotFound();
                }

            }
            catch (Exception e)
            {
                return BadRequest();
            }
        }
    }
}