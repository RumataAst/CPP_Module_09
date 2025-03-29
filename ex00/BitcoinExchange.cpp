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
    if (this->_dataExch.empty())
        return ;

    std::string line, dateStr, valueStr;
    std::string::iterator it;
    
    while (getline(iFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);

        size_t delimiterPos = line.find('|');
        if (delimiterPos == std::string::npos) {
            std::cerr << "Error: Missing '|' delimiter in input: " << line << std::endl;
            continue;
        }
    

        if (std::getline(ss, dateStr, '|') && std::getline(ss, valueStr)) {
            it = std::remove_if(dateStr.begin(), dateStr.end(), std::ptr_fun<int, int>(std::isspace));
            dateStr.erase (it, dateStr.end());
            it = std::remove_if(valueStr.begin(), valueStr.end(), std::ptr_fun<int, int>(std::isspace));
            valueStr.erase (it, valueStr.end());
            
            if (dateStr == "date" &&  valueStr == "value")
                continue;

            if (!(dateStr.length() == 10 &&
                std::isdigit(dateStr[0]) && std::isdigit(dateStr[1]) &&
                std::isdigit(dateStr[2]) && std::isdigit(dateStr[3]) &&
                dateStr[4] == '-' &&
                std::isdigit(dateStr[5]) && std::isdigit(dateStr[6]) &&
                dateStr[7] == '-' &&
                std::isdigit(dateStr[8]) &&
                (std::isdigit(dateStr[9]) || dateStr[9] == '\0'))) 
                continue;

            time_struct ts = parseDate(dateStr);
            finance_struct fs = parseNumber(valueStr);
            if (!ts.isValid() || dateStr.empty()) {
                std::cerr << "Error: Incorrect date format. " << dateStr << std::endl;
                continue;
            }
            if (!fs.isNumberValid() || valueStr.empty()) {
                std::cerr << "Error: Incorrect number format. " << valueStr << std::endl;
                continue;
            }
        
            data_csv::iterator it = _dataExch.lower_bound(ts);

            if (it == _dataExch.end() || it->first > static_cast<const time_struct&>(ts)) {
                if (it == _dataExch.begin()) {
                    std::cerr << "Error: No valid exchange rate found before the given time.\n";
                    continue;
                }
                --it;
            }

            double result = fs.number * it->second.number;

            if (fs.number > 0 && it->second.number > 0 &&
                result > std::numeric_limits<int>::max()) {
                std::cerr << "Error: too large number." << std::endl;
                continue;
            }
            std::cout << ts << " => " << fs.number << " * " << it->second.number << " = " << result << std::endl;
        }
        else {
            if (dateStr.empty() || !parseDate(dateStr).isValid()) {
                std::cerr << "Error: Incorrect date format or empty date: " << dateStr << std::endl;
                continue;
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
