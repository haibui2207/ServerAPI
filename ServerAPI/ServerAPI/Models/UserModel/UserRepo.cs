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

        public User Add(User newUser)
        {
            newUser.id = _nextID;
            _nextID++;
            listData.Add(newUser);
            return newUser;
        }

        public User Remove(User removeUser)
        {
            int index = listData.FindIndex(
                item => item.name == removeUser.name
                        && item.RFID == removeUser.RFID
            );
            listData.RemoveAt(index);
            return removeUser;
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
