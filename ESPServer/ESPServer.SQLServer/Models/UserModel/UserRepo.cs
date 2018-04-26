using System;
using System.Linq;
using System.Threading.Tasks;
using ESPServer.SQLServer.ESPServerContext;

namespace ESPServer.SQLServer.Models.UserModel
{
    public class UserRepo : IUserRepo
    {
        private readonly ESPSeverContext _context;

        public UserRepo(ESPSeverContext context)
        {
            this._context = context;
        }

        public async Task<User> Add(User newUser)
        {
            try
            {
                await _context.Users.AddAsync(newUser);
                await _context.SaveChangesAsync();
                return newUser;
            }
            catch(Exception e)
            {
                throw e;
            }
        }

        public User Remove(User removeUser)
        {
            try
            {
                var user = _context.Users.Single(item => 
                    item.name == removeUser.name && 
                    item.RFID == removeUser.RFID);
                _context.Users.Remove(user);
                _context.SaveChanges();

                return user;
            }
            catch(Exception e)
            {
                throw e;
            }
        }

        public User GetDataByRFID(string RFID)
        {
            try
            {
                return _context.Users.Single(item => item.RFID == RFID);
            }
            catch (Exception e)
            {
                throw e;
            }
        }
    }
}
