#include "BitcoinExchange.hpp"

bool time_struct::isLeapYear() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

bool    time_struct::operator<(const time_struct& ts) const {
        return time_to_days < ts.time_to_days;
}

bool time_struct::operator>(const time_struct& ts) const {
    return time_to_days > ts.time_to_days;
}

bool    time_struct::isValid() const {
    if (month < 1 || month > 12) 
        return false;

    int max_days = 31;
    
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        max_days = 30;
    } else if (month == 2) {
        max_days = isLeapYear() ? 29 : 28;
    }

    return (days >= 1 && days <= max_days);
}

std::ostream &operator<<(std::ostream &os, const time_struct &ts) {
    if (ts.isValid()) {
        os << ts.year << "-" 
            << (ts.month < 10 ? "0" : "") << ts.month << "-" 
            << (ts.days < 10 ? "0" : "") << ts.days;
    }
    return os;
}
