using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using ServerAPI.Models.UserModel;

namespace ServerAPI.Controllers
{
    [Produces("application/json")]
    [Route("api/User")]
    public class UserController : Controller
    {
        static readonly IUserRepo repository = new UserRepo();

        // GET api/User/{RFID}
        [HttpGet("{RFID}")]
        public IActionResult Get(string RFID)
        {
            try
            {
                return Ok(repository.GetDataByRFID(RFID));
            }
            catch (Exception e)
            {
                return NotFound();
            }
        }

        // POST api/User
        [HttpPost]
        public IActionResult Post([FromBody] User newUser)
        {
            try
            {
                if (newUser.name == null || newUser.RFID == null)
                {
                    return BadRequest();
                }

                bool check = repository.Add(newUser);
                if (check) return Ok("Add User Successed.");
                else return BadRequest();
            }
            catch (Exception e)
            {
                return BadRequest();
            }
        }

        // POST api/User
        [HttpDelete]
        public IActionResult Delete([FromBody] User removedUser)
        {
            try
            {
                if (removedUser.name == null || removedUser.RFID == null)
                {
                    return BadRequest();
                }

                bool check = repository.Remove(removedUser);
                if (check) return Ok("Delete User Successed.");
                else return BadRequest();
            }
            catch (Exception e)
            {
                return BadRequest();
            }
        }
    }
}