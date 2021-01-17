
#include "date_wrap.h"
#include "exceptions.h"
#include <iostream>

namespace mtm{
    
using std::ostream;
using mtm::DateWrap;
using mtm::NegativeDays;
using mtm::InvalidDate;


DateWrap::DateWrap(const int day,const int month,const int year){
    if(!dateIsValid(day,month)){
        throw InvalidDate();
    }
    date=dateCreate(day,month,year);
}

DateWrap& DateWrap::operator=(const DateWrap& date_to_enter){
    if(this==&date_to_enter){
        return *this;
    }
    Date new_date=dateCopy(date_to_enter.date);
    
    dateDestroy(date);
    date=new_date;
    return *this;
}

/*DateWrap::DateWrap(int days){
    if(days<0){
        throw NegativeDays();
    }
    int day=0,month=0,year=0;
    while(days>364){
        ++year;
        days-=365;
    }
    while(days>30){
        ++month;
        days-=30;
    }
    day=days;
    date=dateCreate(day,month,year);
}*/

int DateWrap::day() const{
    int* day=new int(0);
    int* month=new int(0);
    int* year=new int(0);
    dateGet(date,day,month,year);
    int day_copy=*day;
    delete day;
    delete month;
    delete year;
    return day_copy;
}

int DateWrap::month() const{
    int* day=new int(0);
    int* month=new int(0);
    int* year=new int(0);
    dateGet(date,day,month,year);
    int month_copy=*month;
    delete day;
    delete month;
    delete year;
    return month_copy;
}

int DateWrap::year() const{
    int* day=new int(0);
    int* month=new int(0);
    int* year=new int(0);
    dateGet(date,day,month,year);
    int year_copy=*year;
    delete day;
    delete month;
    delete year;
    return year_copy;
}

ostream& operator<<(ostream& os,const DateWrap& date){
    os<<date.day()<<'/'<<date.month()<<'/'<<date.year();
    return os;
}

bool DateWrap::operator>(const DateWrap& cmp_date) const{
    return (dateCompare(date,cmp_date.date)>0?true:false);
}

bool DateWrap::operator<(const DateWrap& cmp_date) const{
    return (dateCompare(date,cmp_date.date)<0?true:false);
}

bool operator==(const DateWrap& date1,const DateWrap& date2){
    return(!(date1<date2)&&!(date1>date2)?true:false);
}

bool operator>=(const DateWrap& date1,const DateWrap& date2){
    return((date1==date2)||(date1>date2)?true:false);
}

bool operator<=(const DateWrap& date1,const DateWrap& date2){
    return((date1==date2)||(date1<date2)?true:false);
}

bool operator!=(const DateWrap& date1,const DateWrap& date2){
    return(!(date1==date2)?true:false);
}


DateWrap DateWrap::operator++(int){
    DateWrap copy(*this);
    dateTick(date);
    return copy;
}

DateWrap& DateWrap::operator+=(int days){
    if(days<0){
        throw NegativeDays();
    }
    for(int i=0;i<days;i++){
        (*this)++;
    }
    return *this;
}

DateWrap::DateWrap(const DateWrap& date_to_copy){
    date=dateCopy(date_to_copy.date);
}

DateWrap operator+(int days,DateWrap date){
    if(days<0){
        throw NegativeDays();
    }
    while(days>0){
        date++;
        --days;
    }
    return date;
}

DateWrap operator+(DateWrap date,int days){
        if(days<0){
        throw NegativeDays();
    }
    while(days>0){
        date++;
        --days;
    }
    return date;
}

DateWrap::~DateWrap(){
    dateDestroy(date);
}
/*int dateToInt(DateWrap date){
    return(date.day()+(date.month()*30)+(date.year()*365));
}

DateWrap operator+(const DateWrap& date1,const DateWrap& date2){
    DateWrap new_date=date1;
    int days=dateToInt(date2);
    while(days>0){
        new_date++;
        --days;
    }
    return new_date;
}*/


/*mtm::DateWrap::~DateWrap(){
    dateDestroy(this->date);
}


int mtm::DateWrap::dateToInt()const{
    return (day_date+(month_date*30)+(year_date*365));
}
*/
}