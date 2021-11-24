#ifndef DATE_WRAP_H_
#define DATE_WRAP_H_

#include <iostream>

extern "C" 
{
    #include "date.h"
}

namespace mtm
{

    const int MAX_DAY=30;
    const int MIN_DAY=1;
    const int MAX_MONTH=12;
    const int MIN_MONTH=1;

    class DateWrap
    {
        
        Date date;

        /**
        * A static function to help us check if the date is valid or not.
        */
        static bool dateIsValid(int day,int month);

    public:

        DateWrap(int day,int month,int year);
        DateWrap(const DateWrap& date_to_copy);
        ~DateWrap();
        int day() const;
        int month() const;
        int year() const;
        bool operator>(const DateWrap& cmp_date) const;
        bool operator<(const DateWrap& cmp_date) const;
        DateWrap operator++(int);
        DateWrap& operator=(const DateWrap& date_to_enter);
        DateWrap& operator+=(int days);

    };

    std::ostream& operator<<(std::ostream& os,const DateWrap& date);

    bool operator==(const DateWrap& date1,const DateWrap& date2);

    bool operator>=(const DateWrap& date1,const DateWrap& date2);

    bool operator<=(const DateWrap& date1,const DateWrap& date2);

    bool operator!=(const DateWrap& date1,const DateWrap& date2);

    DateWrap operator+(int days,const DateWrap& date);

    DateWrap operator+(const DateWrap& date,int days);

}

#endif /* DATE_WRAP_H */