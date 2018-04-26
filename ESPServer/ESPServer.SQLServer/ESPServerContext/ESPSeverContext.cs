using ESPServer.SQLServer.Models;
using ESPServer.SQLServer.Models.UserModel;
using Microsoft.EntityFrameworkCore;

namespace ESPServer.SQLServer.ESPServerContext
{
    public class ESPSeverContext : DbContext
    {
        public ESPSeverContext(DbContextOptions<ESPSeverContext> options) : base(options) { }

        public DbSet<Pin> Pins { get; set; }
        public DbSet<User> Users { get; set; }
    }
}
