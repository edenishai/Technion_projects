#include "date_wrap.h"
#include "exceptions.h"
#include <iostream>

namespace mtm
{
    
    using std::ostream;

    const int EMPTY=0;

    DateWrap::DateWrap(const int day,const int month,const int year)
    {
        if(!dateIsValid(day,month))
        {
            throw InvalidDate();
        }
        date=dateCreate(day,month,year);
        if(date==nullptr)
        {
            throw std::bad_alloc();
        }
    }

    DateWrap::DateWrap(const DateWrap& date_to_copy)
    {
        date=dateCopy(date_to_copy.date);
        if(date==nullptr)
        {
            throw std::bad_alloc();
        }
    }

    DateWrap::~DateWrap()
    {
        dateDestroy(date);
    }

    int DateWrap::day() const
    {
        int* day=new int(EMPTY);
        int* month=new int(EMPTY);
        int* year=new int(EMPTY);
        dateGet(date,day,month,year);
        int day_copy=*day;
        delete day;
        delete month;
        delete year;
        return day_copy;
    }

    int DateWrap::month() const
    {
        int* day=new int(EMPTY);
        int* month=new int(EMPTY);
        int* year=new int(EMPTY);
        dateGet(date,day,month,year);
        int month_copy=*month;
        delete day;
        delete month;
        delete year;
        return month_copy;
    }

    int DateWrap::year() const
    {
        int* day=new int(EMPTY);
        int* month=new int(EMPTY);
        int* year=new int(EMPTY);
        dateGet(date,day,month,year);
        int year_copy=*year;
        delete day;
        delete month;
        delete year;
        return year_copy;
    }

    bool DateWrap::operator>(const DateWrap& cmp_date) const
    {
        return (dateCompare(date,cmp_date.date)>0?true:false);
    }

    bool DateWrap::operator<(const DateWrap& cmp_date) const
    {
        return (dateCompare(date,cmp_date.date)<0?true:false);
    }

    DateWrap DateWrap::operator++(int)
    {
        DateWrap copy(*this);
        dateTick(date);
        return copy;
    }

    DateWrap& DateWrap::operator=(const DateWrap& date_to_enter)
    {
        if(this==&date_to_enter)
        {
            return *this;
        }
        Date new_date=dateCopy(date_to_enter.date);
        if(new_date==nullptr)
        {
            throw std::bad_alloc();
        }
        dateDestroy(date);
        date=new_date;
        return *this;
    }

    DateWrap& DateWrap::operator+=(int days)
    {
        if(days<0)
        {
            throw NegativeDays();
        }
        for(int i=0;i<days;i++)
        {
            (*this)++;
        }
        return *this;
    }

    ostream& operator<<(ostream& os,const DateWrap& date)
    {
        os<<date.day()<<'/'<<date.month()<<'/'<<date.year();
        return os;
    }

    bool operator==(const DateWrap& date1,const DateWrap& date2)
    {
        return(!(date1<date2)&&!(date1>date2)?true:false);
    }

    bool operator>=(const DateWrap& date1,const DateWrap& date2)
    {
        return((date1==date2)||(date1>date2)?true:false);
    }

    bool operator<=(const DateWrap& date1,const DateWrap& date2)
    {
        return((date1==date2)||(date1<date2)?true:false);
    }

    bool operator!=(const DateWrap& date1,const DateWrap& date2)
    {
        return(!(date1==date2)?true:false);
    }

    DateWrap operator+(int days,const DateWrap& date)
    {
        if(days<0)
        {
            throw NegativeDays();
        }
        DateWrap new_date=date;
        while(days>0)
        {
            new_date++;
            --days;
        }
        return new_date;
    }

    DateWrap operator+(const DateWrap& date,int days)
    {
        return days+date;
    }

    /**
     * A static function to help us check if the value is valid or not.
     */
    bool DateWrap::dateIsValid(int day,int month)
    {
        if(day<MIN_DAY||day>MAX_DAY||month<MIN_MONTH||month>MAX_MONTH)
        {
            return false;
        }
        return true;
    }

}