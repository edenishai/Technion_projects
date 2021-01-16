#ifndef DATE_WRAP_H
#define DATE_WRAP_H

extern "C" {
    #include "../provided/date.h"
}
#include <iostream>
using std::ostream;

namespace mtm {
    class DateWrap {
        Date date;
    public:
        DateWrap(int day, int month, int year);
        ~DateWrap() = default;
        int day() const;
        int month() const;
        int year() const;
        bool operator>(const DateWrap& d) const;
        bool operator<(const DateWrap& d) const;
        bool operator==(const DateWrap& d) const;
        bool operator>=(const DateWrap& d) const;
        bool operator<=(const DateWrap& d) const;
        bool operator!=(const DateWrap& d) const;
        DateWrap operator++(int); 
        DateWrap& operator+=(const int days);
    };
}

ostream& operator<<(ostream& os, const mtm::DateWrap& date);

#endif /* DATE_WRAP_H */