using System;
using System.Linq;
using ESPServer.Sqlite.Context;
using ESPServer.Sqlite.Models;
using ESPServer.Sqlite.Models.UserModel;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;

namespace ESPServer.Sqlite.Data
{
    public class SeedData
    {
        public static void Initialize(IServiceProvider serviceProvider)
        {
            using (var context = new ESPServerContext(
                serviceProvider.GetRequiredService<DbContextOptions<ESPServerContext>>()))
            {
                if (context.Pins.Any() && context.Users.Any()) // If Data none Empty , return
                {
                    return;
                }
                if (!context.Pins.Any())
                {
                    context.Pins.AddRange(
                        new Pin(1, 0),
                        new Pin(2, 0),
                        new Pin(3, 0),
                        new Pin(4, 0),
                        new Pin(5, 0),
                        new Pin(6, 0),
                        new Pin(7, 0),
                        new Pin(8, 0),
                        new Pin(9, 0),
                        new Pin(10, 0),
                        new Pin(11, 0),
                        new Pin(12, 0),
                        new Pin(13, 0),
                        new Pin(14, 0),
                        new Pin(15, 0),
                        new Pin(16, 0),
                        new Pin(17, 0),
                        new Pin(18, 0),
                        new Pin(19, 0),
                        new Pin(20, 0)
                    );
                }
                if (!context.Users.Any())
                {
                    context.Users.AddRange(
                        new User("Hai Bui", "919b8459"),
                        new User("Trung Duyen", "27a5a059")
                    );

                }

                context.SaveChanges();
            }
        }
    }
}
