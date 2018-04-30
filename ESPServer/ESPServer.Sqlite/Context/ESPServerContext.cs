using ESPServer.Sqlite.Models;
using ESPServer.Sqlite.Models.UserModel;
using Microsoft.EntityFrameworkCore;

namespace ESPServer.Sqlite.Context
{
    public class ESPServerContext : DbContext
    {
        public ESPServerContext(DbContextOptions<ESPServerContext> options) : base(options) { }

        public DbSet<Pin> Pins { get; set; }
        public DbSet<User> Users { get; set; }
    }
}

