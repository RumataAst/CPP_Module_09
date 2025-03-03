#include "RPN.hpp"
#include <cctype>
#include <cstdlib>
#include <string>
#include <string.h>

RPN::RPN() : _dataRPN() {}

RPN::RPN(const RPN &copy) : _dataRPN(copy._dataRPN) {}

RPN &RPN::operator=(const RPN &source) {
    if (this != &source) {
        this->_dataRPN = source._dataRPN;
    }
    return *this;
}

RPN::~RPN() {}

int RPN::perform_operation(char c, int value_1, int value_2) {
    switch (c) {
        case '+': return value_1 + value_2;
        case '-': return value_1 - value_2;
        case '*': return value_1 * value_2;
        case '/': 
            if (value_2 != 0) 
                return value_1 / value_2;
            std::cerr << "Error: Division by zero\n";
            exit(EXIT_FAILURE);
        default:
            std::cerr << "Error: Invalid operator '" << c << "'\n";
            exit(EXIT_FAILURE);
    }
}

void RPN::calculate_RPN(std::string &data) {
    std::string::iterator   it;
    int                     value_1, value_2, result;
    std::string             operator = "+-*/";

    // Remove whitespace characters
    it = std::remove_if(data.begin(), data.end(), std::ptr_fun<int, int>(std::isspace));
    data.erase(it, data.end());

    for (size_t i = 0; i < data.length(); ++i) {
        char c = data[i];

        if (std::isdigit(c)) {
            _dataRPN.push(c - '0');
        } 
        else if (operator.find(c) != std::string::npos) {
            if (_dataRPN.size() < 2) {
                std::cerr << "Error: Not enough operator for operator: " << c << "'\n";
                return;
            }
            value_2 = _dataRPN.top();
            _dataRPN.pop();
            value_1 = _dataRPN.top();
            _dataRPN.pop();

            result = perform_operation(c, value_1, value_2);
            _dataRPN.push(result);
        } 
        else {
            std::cerr << "Error: Invalid character '" << c << "'\n";
            return;
        }
    }

    if (_dataRPN.size() != 1) {
        std::cerr << "Error: Invalid RPN expression\n";
    } else {
        std::cout << _dataRPN.top() << std::endl;
    }
}