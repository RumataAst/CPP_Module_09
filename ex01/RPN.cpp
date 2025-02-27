#include "RPN.hpp"

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
    std::string         operatorVal, operandVal;

    for (int i = 0; data[i]; ++i) {

        if (i % 2 != 0) {
            std::getline(ss, operatorVal, ' ');
            std::cout << operatorVal << std::endl;
        }
        else {
            std::getline(ss, operandVal, ' ');
            std::cout << operandVal << std::endl;
        }
    }
}