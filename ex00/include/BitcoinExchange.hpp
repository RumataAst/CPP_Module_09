# ifndef BITCOIN_EXCHANGE_HPP 
#define BITCOIN_EXCHANGE_HPP

#include <iostream>     // for string
#include <map>          // for map
#include <fstream>      // reading from file
#include <sstream>      // stringstream
#include <string>       // find
#include <stdexcept>    // exception
#include <stdlib.h>     // strtod
#include <limits>       // limits
#include <cfloat>       // dbl_max
#include <algorithm>    // remove spaces
#include <cctype>       // isSpace

// it's overcomplicated for the current exercise but i just want to have more practise
struct finance_struct {
    std::string     valueStr;
    double          number;

    bool    isNumberValid() const;
    bool    operator<(const finance_struct& fs) const;
};

struct time_struct {
    std::string     dateStr;
    int days;
    int month;
    int year;
    int time_to_days;

    bool isLeapYear() const;
    bool isValid() const;
    bool operator<(const time_struct& ts) const;
    bool operator>(const time_struct& ts) const;
};

#define data_csv std::map<time_struct, finance_struct>

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
    
    finance_struct  parseNumber(const std::string &number) const;
    time_struct     parseDate(const std::string &date) const;

    void            showMerge(std::ifstream &iFile);
};

// operator << for time_struct
std::ostream &operator<<(std::ostream &os, const time_struct &ts);

//operator << for class BitcoinExchange
std::ostream &operator<<(std::ostream &os, const BitcoinExchange &be);

//opeator << for finance_struct
std::ostream &operator<<(std::ostream &os, const finance_struct &fs);

#endif