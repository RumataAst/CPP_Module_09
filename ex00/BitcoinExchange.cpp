#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
    try {
        fromCsvToMap(_dataExch);
    } 
    catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    } 
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) {
    this->_dataExch = copy.getDataExch();
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &source) {
    if (this != &source) {
        this->_dataExch = source.getDataExch();
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

const data_csv    &BitcoinExchange::getDataExch() const {
        return _dataExch;
}

time_struct BitcoinExchange::parseDate(const std::string &date) const{
    time_struct ts;
    char dash;
    ts.dateStr = date;

    std::stringstream ss(date);
    ss >> ts.year >> dash >> ts.month >> dash >> ts.days;

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (ts.isLeapYear()) {
        days_in_month[1] = 29;
    }

    ts.time_to_days = 0;
    for (int i = 0; i < ts.month - 1; ++i) {
        ts.time_to_days += days_in_month[i];
    }
    ts.time_to_days += ts.days;
    ts.time_to_days += (ts.year - 1) * 365 + (ts.year - 1) / 4 - (ts.year - 1) / 100 + (ts.year - 1) / 400;

    // if (!ts.isValid())
    //     throw std::invalid_argument("Invalid date format: " + date); 
    return ts;
}

finance_struct BitcoinExchange::parseNumber(const std::string &numberStr) const{
    finance_struct  fs;
    char*           pEnd;
    
    fs.valueStr = numberStr;
    fs.number = strtod(numberStr.c_str(), &pEnd);

    return fs;
}

void BitcoinExchange::fromCsvToMap(data_csv &data) const {
    std::ifstream iFile("data.csv");
    if (!iFile.is_open()) {
        throw std::runtime_error("File could not be opened.");
    }

    std::string line, dateStr, valueStr;
    double value = 0;

    data.clear();
    while (getline(iFile, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        if (std::getline(ss, dateStr, ',') && std::getline(ss, valueStr)) {
            std::stringstream valueStream(valueStr);
            if (!(valueStream >> value)) {
                continue;
            }

            time_struct ts = parseDate(dateStr);
            finance_struct fs = parseNumber(valueStr);
            data[ts] = fs;
        }
    }
    iFile.close();
}

void BitcoinExchange::showMerge(std::ifstream &iFile) {
    std::string line, dateStr, valueStr;

    while (getline(iFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        
        if (std::getline(ss, dateStr, '|') && std::getline(ss, valueStr)) {
            // Parse the date and value
            time_struct ts = parseDate(dateStr);
            finance_struct fs = parseNumber(valueStr);
            if (line == "date | value")
                continue;
            if (!ts.isValid() ||!fs.isNumberValid()) {
                continue;
            }
        data_csv::iterator it = _dataExch.lower_bound(ts);

        if (it != _dataExch.end()) {
            double result = fs.number * it->second.number;
            std::cout << ts << " => " << fs.number << " * " << it->second.number << " = " << result << std::endl;
        } else {
            --it;
            double result = fs.number * it->second.number;  // Multiply values
            if (result > DBL_MAX) {
                std::cerr << "Error: multiplication result exceeds maximum double limit." << std::endl;
            } else {
                std::cout << ts << " => " << fs.number << " * " << it->second.number << " = " << result << std::endl;
            }
        }
        }
    }
}



std::ostream &operator<<(std::ostream &os, const BitcoinExchange &be) {
    if (!be.getDataExch().empty()) {
        data_csv::const_iterator it;

        for (it = be.getDataExch().begin(); it != be.getDataExch().end(); ++it) {
            os << "Date is " << it->first << " Value is " << it->second << std::endl;
        }
    }
    return os;
}
