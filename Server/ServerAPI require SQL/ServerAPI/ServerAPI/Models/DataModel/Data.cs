using System.ComponentModel.DataAnnotations;

namespace ServerAPI.Models
{
    public class Data
    {
        public int id { get; set; }
        [Required]
        [Range(0, 20)]
        public int pin { get; set; }
        [Required]
        [Range(0, 1)]
        public int state { get; set; }

        public Data() { }

        public Data(int pin, int state)
        {
            this.pin = pin;
            this.state = state;
        }
    }
}
