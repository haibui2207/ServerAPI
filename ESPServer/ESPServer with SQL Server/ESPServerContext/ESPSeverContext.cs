using ESPServer_with_SQL_Server.Models;
using ESPServer_with_SQL_Server.Models.UserModel;
using Microsoft.EntityFrameworkCore;

namespace ESPServer_with_SQL_Server.ESPServerContext
{
    public class ESPSeverContext : DbContext
    {
        public ESPSeverContext(DbContextOptions<ESPSeverContext> options) : base(options) { }

        public DbSet<Pin> Pins { get; set; }
        public DbSet<User> Users { get; set; }
    }
}
