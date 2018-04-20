using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using ServerAPI.DataContext;
using ServerAPI.Models;
using ServerAPI.Models.UserModel;

namespace ServerAPI.DataDefault
{
    public class SeedData
    {
        public static void Initialize(IServiceProvider serviceProvider)
        {
            using (var context = new ServerAPIContext(
                serviceProvider.GetRequiredService<DbContextOptions<ServerAPIContext>>()))
            {
                if (context.Pins.Any() && context.Users.Any()) // If Data none Empty , return
                {
                    return;
                }                
                if (!context.Pins.Any())
                {
                    context.Pins.AddRange(
                        new Data(1, 0),
                        new Data(2, 0),
                        new Data(3, 0),
                        new Data(4, 0),
                        new Data(5, 0),
                        new Data(6, 0),
                        new Data(7, 0),
                        new Data(8, 0),
                        new Data(9, 0),
                        new Data(10, 0),
                        new Data(11, 0),
                        new Data(12, 0),
                        new Data(13, 0),
                        new Data(14, 0),
                        new Data(15, 0),
                        new Data(16, 0),
                        new Data(17, 0),
                        new Data(18, 0),
                        new Data(19, 0),
                        new Data(20, 0)
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
