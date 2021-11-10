#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include "datetime.h"
#include <iomanip>

using namespace std;

DateTime::DateTime()
{
    time_t rawtime;
    //struct that will store the current local time variabls (hour, min, sec, etc.)
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    //after setting localtime variables into struct, extract information from struct
    //data members of datetime object
    hour = timeinfo->tm_hour;
    min = timeinfo->tm_min;
    sec = timeinfo->tm_sec;
    year = 1900 + timeinfo->tm_year;
    month = 1 + timeinfo->tm_mon;
    day = timeinfo->tm_mday;

}

DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day)
{
    hour = hh;
    min = mm;
    sec = ss;
    this->year = year;
    this->month = month;
    this->day = day;

}

//checks whether this object came before other object 
//comparing from year all the way down to second
bool DateTime::operator<(const DateTime& other) const
{
    if (year < other.year)
    {
        return true;
    }

    else if (year > other.year)
    {
        return false;
    }

    else
    {
        if (month < other.month)
        {
            return true;
        }

        else if (month > other.month)
        {
            return false;
        }

        else
        {
            if (day < other.day)
            {
                return true;
            }

            else if (day > other.day)
            {
                return false;
            }

            else
            {
                if (hour < other.hour)
                {
                    return true;
                }

                else if (hour > other.hour)
                {
                    return false;
                }

                else
                {
                    if (min < other.min)
                    {
                        return true;
                    }

                    else if (min > other.min)
                    {
                        return false;
                    }

                    else
                    {
                        if (sec < other.sec)
                        {
                            return true;
                        }

                        else
                        {
                            return false;
                        }

                    }
                }
            }
        }
    }
}

ostream& operator<<(ostream& os, const DateTime& other)
{
    os << other.year << '-' << setfill('0') << setw(2) << other.month << '-' << setfill('0') << setw(2) << other.day << ' '
    << setfill('0') << setw(2) << other.hour << ':' << setfill('0') << setw(2) << other.min << ':' 
    << setfill('0') << setw(2) << other.sec;

    return os;
}

//expecting YYYY-MM-DD HH:MM:SS format, extract necessary information and
//update data members
istream& operator>>(istream& is, DateTime& dt)
{
    //create datetime object with current time
    DateTime temp;
    string date_extract;
    stringstream ss_temp;
    //use getline to store year in date_extract
    getline(is, date_extract, '-');
    //if extraction fails, update dt to current time and return is
    if (is.fail())
    {
        dt = temp;
        return is;
    }
    //create stringstream with year
    ss_temp.str(date_extract);
    //pull in year as int from stringstream
    ss_temp >> dt.year;
    //if extraction fails, update dt to current time and return is
    if (ss_temp.fail())
    {
        dt = temp;
        return is;
    }
    //make sure ss_temp is empty for reuse
    ss_temp.clear();
    ss_temp.str("");

    //same process but for month
    getline(is, date_extract, '-');
    if (is.fail())
    {
        dt = temp;
        return is;
    }
    ss_temp.str(date_extract);
    ss_temp >> dt.month;

    if (ss_temp.fail())
    {
        dt = temp;
        return is;
    }

    ss_temp.clear();
    ss_temp.str("");

    //same process but for day (don't need to use getline since day
    //is at end of string and is stops at empty space
    is >> date_extract;
    if (is.fail())
    {
        dt = temp;
        return is;
    }
    ss_temp.str(date_extract);
    ss_temp >> dt.day;

    if (ss_temp.fail())
    {
        dt = temp;
        return is;
    }

    ss_temp.clear();
    ss_temp.str("");

    string time_extract;
    //same process but for hour
    getline(is, time_extract, ':');
    if (is.fail())
    {
        dt = temp;
        return is;
    }
    ss_temp.str(time_extract);
    ss_temp >> dt.hour;

    if (ss_temp.fail())
    {
        dt = temp;
        return is;
    }

    ss_temp.clear();
    ss_temp.str("");

    //same process but for min
    getline(is, time_extract, ':');
    if (is.fail())
    {
        dt = temp;
        return is;
    }
    ss_temp.str(time_extract);
    ss_temp >> dt.min;

    if (ss_temp.fail())
    {
        dt = temp;
        return is;
    }
    
    ss_temp.clear();
    ss_temp.str("");

    //same process but for sec
    is >> time_extract;
    if (is.fail())
    {
        dt = temp;
        return is;
    }
    ss_temp.str(time_extract);
    ss_temp >> dt.sec;

    if (ss_temp.fail())
    {
        dt = temp;
        return is;
    }

    ss_temp.clear();
    ss_temp.str("");

    return is;

}

