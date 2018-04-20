using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using ServerAPI.Models;
using ServerAPI.Models.UserModel;

namespace ServerAPI.DataContext
{
    public class ServerAPIContext : DbContext
    {
        public ServerAPIContext(DbContextOptions<ServerAPIContext> options) : base(options) { }

        public DbSet<Data> Pins { get; set; }
        public DbSet<User> Users { get; set; }
    }
}
