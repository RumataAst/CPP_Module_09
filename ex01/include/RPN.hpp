# ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <algorithm>

class RPN {
private:
    std::stack<int> _dataRPN;

public:
    RPN();
    RPN(const RPN &copy);
    RPN &operator=(const RPN &source);
    ~RPN();

    int     perform_operation(char c, int value_1, int value_2);
    void    calculate_RPN(std::string &data);
};

#endif