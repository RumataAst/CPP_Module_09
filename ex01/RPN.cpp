#include "RPN.hpp"
#include <cctype>

RPN::RPN() : _dataRPN() {}

RPN::RPN(const RPN &copy) {
    this->_dataRPN = copy._dataRPN;
}

RPN &RPN::operator=(const RPN &source) {
    if (this != &source) {
        this->_dataRPN = source._dataRPN;
    }
    return *this;
}

RPN::~RPN() {}

void    RPN::calculate_RPN(std::string &data) {
    std::stringstream   ss(data);
    std::string         value;

    for (int i = 0; data[i]; ++i) {

        std::getline(ss, value, ' ');
        if (isdigit(value)()) {

        }
    }
}