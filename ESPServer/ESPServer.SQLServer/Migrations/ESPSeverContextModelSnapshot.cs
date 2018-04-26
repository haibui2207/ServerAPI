﻿// <auto-generated />
using ESPServer.SQLServer.ESPServerContext;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage;
using Microsoft.EntityFrameworkCore.Storage.Internal;
using System;

namespace ESPServer.SQLServer.Migrations
{
    [DbContext(typeof(ESPSeverContext))]
    partial class ESPSeverContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "2.0.2-rtm-10011")
                .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

            modelBuilder.Entity("ESPServer.SQLServer.Models.Pin", b =>
                {
                    b.Property<int>("id")
                        .ValueGeneratedOnAdd();

                    b.Property<int>("pin");

                    b.Property<int>("state");

                    b.HasKey("id");

                    b.ToTable("Pins");
                });

            modelBuilder.Entity("ESPServer.SQLServer.Models.UserModel.User", b =>
                {
                    b.Property<int>("id")
                        .ValueGeneratedOnAdd();

                    b.Property<string>("RFID")
                        .IsRequired()
                        .HasMaxLength(8);

                    b.Property<string>("name")
                        .IsRequired()
                        .HasMaxLength(20);

                    b.HasKey("id");

                    b.ToTable("Users");
                });
#pragma warning restore 612, 618
        }
    }
}
