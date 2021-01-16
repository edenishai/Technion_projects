#include "date_wrap.h"
using mtm::DateWrap;

ostream& operator<<(ostream& os, const DateWrap& date) {
    return os << date.day() << "/" << date.month() << "/" << date.year() << "\n";
}

DateWrap::DateWrap(int day, int month, int year): 
    date(dateCreate(day, month, year)) {
        if (!date) {
            //TODO: to return InvalidDate exception.
        }
}

int DateWrap::day() const {
    int *day = new int;
    int *month = new int;
    int *year = new int;

    dateGet(this->date, day, month, year);
    int day_copy = *day;

    delete day;
    delete month;
    delete year;

    return day_copy;
}

int DateWrap::month() const {
    int *day = new int;
    int *month = new int;
    int *year = new int;

    dateGet(this->date, day, month, year);
    int month_copy = *month;
    
    delete day;
    delete month;
    delete year;

    return month_copy;
}

int DateWrap::year() const {
    int *day = new int;
    int *month = new int;
    int *year = new int;

    dateGet(this->date, day, month, year);
    int year_copy = *year;
    
    delete day;
    delete month;
    delete year;

    return year_copy;
}