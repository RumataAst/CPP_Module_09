# ifndef BITCOIN_EXCHANGE_HPP 
#define BITCOIN_EXCHANGE_HPP

#include <iostream>     // for string
#include <map>          // for map
#include <fstream>      // reading from file
#include <sstream>      // stringstream
#include <string>       // find
#include <stdexcept>    // exception


struct time_struct {
    int days;
    int month;
    int year;
    int time_to_days;

    bool isLeapYear() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    bool isValid() const {
        if (month < 1 || month > 12) return false;

        int max_days = 31;

        if (month == 4 || month == 6 || month == 9 || month == 11) {
            max_days = 30;
        } else if (month == 2) {
            max_days = isLeapYear() ? 29 : 28;
        }

        return (days >= 1 && days <= max_days);
    }

    // Custom comparison for time_struct to use in std::map
    bool operator<(const time_struct& ts) const {
        return time_to_days < ts.time_to_days;
    }
};

#define data_csv std::map<time_struct, double>

class BitcoinExchange {
private:
    data_csv    _dataExch;

    void        fromCsvToMap(data_csv &data) const;
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &copy);
    BitcoinExchange &operator = (const BitcoinExchange &source);
    ~BitcoinExchange();

    const data_csv    &getDataExch() const;
    
    //helper function
    time_struct parseDate(const std::string &date) const;
    void        showData() const;

    // void        showMerge(std::ifstream iFile) const;

};

// operator << for time_struct
std::ostream &operator<<(std::ostream &os, const time_struct &ts);

//operator << for class BitcoinExchange
std::ostream &operator<<(std::ostream &os, const BitcoinExchange &be);

#endif