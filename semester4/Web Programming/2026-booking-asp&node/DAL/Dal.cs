using _2026_booking.Models;
using exam_asp.Models;
using MySql.Data.MySqlClient;
using System.Data;

namespace exam_asp.DAL
{
    public class Dal
    {
        private readonly string connstring = "server=localhost;uid=root;pwd=;database=2026-booking";

        public User Authentication(String username)
        {
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();
                string query = "SELECT * FROM users WHERE username=@username";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@username", username);
                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            int id = reader.GetInt32("id");
                            string membershipType = reader.GetString("membershipType");
                            return new User(id,username,membershipType);
                        }
                    }
                }
            }
            return null;
        }

        public int GetBookingsForClass(int classID)
        {
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();
                string query = "SELECT count(*) as count FROM bookings WHERE classID=@classID and cancelled=0";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@classID", classID);
                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            int number = reader.GetInt32("count");
                            return number;
                        }
                    }
                }
            }
            return 0;
        }
        public List<ClassPlus> GetUpcommingClasses()
        {
            List<ClassPlus> upcommingClasses = new List<ClassPlus>();
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();
                string query = "SELECT * FROM classes WHERE classDate >= DATE(NOW())";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                { 
                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            int id = reader.GetInt32("id");
                            string className = reader.GetString("className");
                            string instructorName = reader.GetString("instructorName");
                            DateTime classDate = reader.GetDateTime("classDate");
                            int maxCapacity = reader.GetInt32("maxcapacity");
                            int available = maxCapacity-GetBookingsForClass(id);
                            ClassPlus entry =  new ClassPlus(id, className, instructorName, classDate,maxCapacity, available);
                            upcommingClasses.Add(entry);
                        }
                        return upcommingClasses;
                    }
                }
            }
        }
        private bool ClassHighIntensity(int classID)
        {
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();
                string query = "SELECT * FROM classes WHERE id=@classID and className like '%High'";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@classID", classID);
                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            return true;
                        }
                        return false;
                    }
                }
            }
        }

        private string GetUserMembership(int userID)
        {
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();
                string query = "SELECT membershipType FROM users WHERE id=@userID";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@userID", userID);
                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        reader.Read();
                        string membershipType = reader.GetString("membershipType");
                        return membershipType;
                    }
                }
            }
        }

        private Class GetClassById(int classID)
        {
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();
                string query = "SELECT * FROM classes WHERE id=@classID";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@classID", classID);
                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            int id = classID;
                            string className = reader.GetString("className");
                            string instructorName = reader.GetString("instructorName");
                            DateTime classDate = reader.GetDateTime("classDate");
                            int maxCapacity = reader.GetInt32("maxcapacity");
                            Class c = new Class(id, className, instructorName, classDate, maxCapacity);
                            return c;
                        }
                    }
                }
            }
            return null;
        }

        public int UserHasBooking(int userID, int classID)
        {
            using (MySqlConnection conn = new MySqlConnection(connstring))
            {
                conn.Open();
                string query = "SELECT * FROM bookings WHERE userID=@userID and classID=@classID";

                using (MySqlCommand cmd = new MySqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@userID", userID);
                    cmd.Parameters.AddWithValue("@classID", classID);

                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            if (reader.GetInt32("cancelled") == 0) {  return 1; }
                            else
                            {
                                return 2;
                            }
                        }
                        else
                        {
                            return 3;
                        }
                    }
                }
            }
        }
        public string Book(int userID, int classID)
        {
            if(GetUserMembership(userID)=="basic" && ClassHighIntensity(classID))
            {
                return "Only premium members have access to high intensity classes";
            }
            //check daca are book
            if (UserHasBooking(userID, classID)==1)
            {
                return "you have already booked this class";
            }
            else
            {
                if(UserHasBooking(userID, classID) == 2)
                {
                    int maxCapacity = GetClassById(classID).maxCapacity;
                    if (maxCapacity - GetBookingsForClass(classID) <= 0)
                    {
                        //add to waiting list
                        using (MySqlConnection conn = new MySqlConnection(connstring))
                        {
                            conn.Open();
                            string query = "Insert into waitlist (userID,classID,addedAt) values (@userID,@classID,DATE(NOW()))";

                            using (MySqlCommand cmd = new MySqlCommand(query, conn))
                            {
                                cmd.Parameters.AddWithValue("@userID", userID);
                                cmd.Parameters.AddWithValue("@classID", classID);

                                cmd.ExecuteNonQuery();
                            }
                        }
                        return "you have been added to the waiting list";
                    }
                    else
                    {
                        using (MySqlConnection conn = new MySqlConnection(connstring))
                        {
                            conn.Open();
                            string query = "update waitlist set cancelled=0 where userID=@userID and classID=@classID";

                            using (MySqlCommand cmd = new MySqlCommand(query, conn))
                            {
                                cmd.Parameters.AddWithValue("@userID", userID);
                                cmd.Parameters.AddWithValue("@classID", classID);

                                cmd.ExecuteNonQuery();
                            }
                        }
                        return "booking sucessfull";
                        //add book
                        //update to 1
                    }
                }
                else
                {
                    int maxCapacity = GetClassById(classID).maxCapacity;
                    if (maxCapacity - GetBookingsForClass(classID) <= 0)
                    {
                        using (MySqlConnection conn = new MySqlConnection(connstring))
                        {
                            conn.Open();
                            string query = "Insert into waitlist (userID,classID,addedAt) values (@userID,@classID,DATE(NOW()))";

                            using (MySqlCommand cmd = new MySqlCommand(query, conn))
                            {
                                cmd.Parameters.AddWithValue("@userID", userID);
                                cmd.Parameters.AddWithValue("@classID", classID);

                                cmd.ExecuteNonQuery();
                            }
                        }
                        //add to waiting list
                        return "you have been added to the waiting list";

                    }
                    else
                    {
                        using (MySqlConnection conn = new MySqlConnection(connstring))
                        {
                            conn.Open();
                            string query = "Insert into bookings (userID,classID,bookedAt,cancelled) values (@userID,@classID,DATE(NOW()),0)";

                            using (MySqlCommand cmd = new MySqlCommand(query, conn))
                            {
                                cmd.Parameters.AddWithValue("@userID", userID);
                                cmd.Parameters.AddWithValue("@classID", classID);

                                cmd.ExecuteNonQuery();
                            }
                        }
                        return "booking sucessfull";

                        //add book
                    }
                }
            }
        }
    }
}
