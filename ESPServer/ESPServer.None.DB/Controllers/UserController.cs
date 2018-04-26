using System;
using ESPServer_None_DB.Models.UserModel;
using Microsoft.AspNetCore.Mvc;

namespace ESPServer_None_DB.Controllers
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

                User addedUser= repository.Add(newUser);
                if (addedUser != null) return Ok("Add User Successed.");
                else return BadRequest();
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
                if (deletedUser.name == null || deletedUser.RFID == null)
                {
                    return BadRequest();
                }

                User removedUser = repository.Remove(deletedUser);
                if (removedUser != null) return Ok("Delete User Successed.");
                else return BadRequest();
            }
            catch (Exception e)
            {
                return BadRequest();
            }
        }
    }
}