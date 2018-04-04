using System.ComponentModel.DataAnnotations;

namespace ServerAPI.Models
{
    public class Data
    {
        [Range(0, 20)]
        public int pin { get; set; }
        [Range(0, 1)]
        public int state { get; set; }

        public Data(int pin, int state)
        {
            this.pin = pin;
            this.state = state;
        }
    }
}
