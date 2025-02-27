#include "BitcoinExchange.hpp"

bool    struct_finance::isNumberValid() const {
    if (valueStr == "0")
        return true;
    char* pEnd;
    number = strod(valueStr, &pEnd);
}


bool struct_finance::operator<(const finance_stuct& fs) const {
    return cents < fs.cents;
}

std::ostream &operator<<(std::ostream &os, const finance_stuct &fs) {
    if (!fs.isNumberValid()) {
        os << "Bad format";
    } else {
        
    }
    return os;
}
