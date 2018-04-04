using System;
using System.Collections.Generic;

namespace ServerAPI.Models.UserModel
{
    public class UserRepo : IUserRepo
    {
        private List<User> listData = new List<User>();
        private int _nextID = 1;

        public UserRepo()
        {
            Add(new User("Hai Bui", "919b8459"));
            Add(new User("Trung Duyen", "27a5a059"));
        }

        public bool Add(User newUser)
        {
            try
            {
                newUser.id = _nextID;
                _nextID++;
                listData.Add(newUser);
                return true;
            }
            catch (Exception e)
            {
                return false;
            }
        }

        public bool Remove(User removeUser)
        {
            try
            {
                int index = listData.FindIndex(
                    item => item.name == removeUser.name 
                            && item.RFID == removeUser.RFID
                            );
                listData.RemoveAt(index);
                return true;
            }
            catch (Exception e)
            {
                return false;
            }
        }

        public User GetDataByRFID(string RFID)
        {
            foreach (var item in listData)
            {
                if (item.RFID == RFID)
                    return item;
            }
            return null;
        }
    }
}
