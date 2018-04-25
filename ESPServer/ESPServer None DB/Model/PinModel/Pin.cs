using System.ComponentModel.DataAnnotations;

namespace ESPServer_None_DB.Models
{
    public class Pin
    {
        [Range(0, 20)]
        public int pin { get; set; }
        [Range(0, 1)]
        public int state { get; set; }

        public Pin(int pin, int state)
        {
            this.pin = pin;
            this.state = state;
        }
    }
}
