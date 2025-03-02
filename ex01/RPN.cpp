#include "RPN.hpp"
#include <cctype>
#include <cstdlib>
#include <string>
#include <string.h>

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

int     RPN::perform_operation(char c, int value_1, int value_2) {
    if (c == '+')
        return value_1 + value_2;
    else if (c == '-')
        return value_1 - value_2;
    else if (c == '*')
        return value_1 * value_2;
    else if (c == '/' && value_2 != 0)
        return value_1 / value_2;
    return -1;
}

void    RPN::calculate_RPN(std::string &data) {
    std::string::iterator       it;
    int                         value_1, value_2, result;
    std::string                 operands = "+-*/";
    const char *                array = operands.c_str();
    const char *                initial_array = NULL;

    it = std::remove_if(data.begin(), data.end(), std::ptr_fun<int, int>(std::isspace));
    data.erase (it, data.end());
    initial_array = data.c_str();

    for (size_t i = 0; initial_array[i]; ++i) {
        if (strchr(array, initial_array[i]) == NULL){
            _dataRPN.push(initial_array[i] - '0');
        }
        else if (strchr(array, initial_array[i]) != NULL && _dataRPN.size() >= 2) {
            value_2 = _dataRPN.top();
            _dataRPN.pop();
            value_1 = _dataRPN.top();
            _dataRPN.pop();

            result = perform_operation(initial_array[i], value_1, value_2);
            if (result == -1) {
                std::cerr << "ERROR\n" << std::endl;
                return ;
            }
            _dataRPN.push(result);
        }
        else {
            std::cout << "Error\n";
            return ;
        }
    }
    
    if (_dataRPN.size() != 1) {
        std::cout << "Error\n";
    }
    else {
       std::cout << _dataRPN.top() << std::endl;
    }

}