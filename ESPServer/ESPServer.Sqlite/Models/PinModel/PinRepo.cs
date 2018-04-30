using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ESPServer.Sqlite.Context;

namespace ESPServer.Sqlite.Models
{
    public class PinRepo : IPinRepo
    {
        private readonly ESPServerContext _context;

        public PinRepo(ESPServerContext context)
        {
            this._context = context;
        }

        public IEnumerable<Pin> GetAll()
        {
            try
            {
                return _context.Pins.ToArray();
            }
            catch (Exception e)
            {
                return null;
            }
        }

        public async Task<Pin> Add(Pin data)
        {
            try
            {
                await _context.AddAsync(data);
                await _context.SaveChangesAsync();

                return data;
            }
            catch(Exception e)
            {
                throw e;
            }
        }

        public async Task<Pin> ChangData(Pin data)
        {
            try
            {
                var oldData = _context.Pins.Single(item => item.pin == data.pin);
                oldData.state = data.state;
                _context.Update(oldData);
                await _context.SaveChangesAsync();

                return data;
            }
            catch (Exception e)
            {
                throw e;
            }
        }

        public async Task<bool> ResetAllPin()
        {
            try
            {
                foreach (var item in _context.Pins)
                {
                    item.state = 0;
                    _context.Update(item);
                }
                await _context.SaveChangesAsync();

                return true;
            }
            catch (Exception e)
            {
                return false;
            }
        }

        public Pin GetDataByPin(int pin)
        {
            try
            {
                return _context.Pins.Single(item => item.pin == pin);
            }
            catch (Exception e)
            {
                throw e;
            }
        }
    }
}
