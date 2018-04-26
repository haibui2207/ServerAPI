using System.ComponentModel.DataAnnotations;

namespace ESPServer.SQLServer.Models
{
    public class Pin
    {
        public int id { get; set; }
        [Required]
        [Range(0, 20)]
        public int pin { get; set; }
        [Required]
        [Range(0, 1)]
        public int state { get; set; }

        public Pin() { }

        public Pin(int pin, int state)
        {
            this.pin = pin;
            this.state = state;
        }
    }
}
