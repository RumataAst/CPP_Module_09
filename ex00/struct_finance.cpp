#include "BitcoinExchange.hpp"
#include <climits>

bool finance_struct::isNumberValid() const {
    if (valueStr == "0") {
        return true;
    }

    char* pEnd;
    double value = strtod(valueStr.c_str(), &pEnd);

    if (value <= 0) {
        // std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }

    if (value > std::numeric_limits<double>::max()) {
        // std::cerr << "Error: number exceeds maximum double limit." << std::endl;
        return false;
    }

    if (*pEnd != '\0' && *pEnd != 'f') {
        // std::cerr << "Error: bad format." << std::endl;
        return false;
    }

    return true;
}


bool finance_struct::operator<(const finance_struct& fs) const {
    return number < fs.number;
}

std::ostream &operator<<(std::ostream &os, const finance_struct &fs) {
    if (fs.isNumberValid()) {
        os << fs.number;
    }
    return os;
}
