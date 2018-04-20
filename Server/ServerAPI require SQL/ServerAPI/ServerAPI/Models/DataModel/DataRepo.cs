using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ServerAPI.DataContext;

namespace ServerAPI.Models
{
    public class DataRepo : IDataRepo
    {
        private readonly ServerAPIContext _context;

        public DataRepo(ServerAPIContext context)
        {
            this._context = context;
        }

        public IEnumerable<Data> GetAll()
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

        public async Task<Data> Add(Data data)
        {
            try
            {
                await _context.AddAsync(data);
                return data;
            }
            catch(Exception e)
            {
                throw e;
            }
        }

        public async Task<Data> ChangData(Data data)
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

        public Data GetDataByPin(int pin)
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
