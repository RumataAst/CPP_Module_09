# ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>

class RPN {
private:
    std::stack<int> _dataRPN;

public:
    RPN();
    RPN(const RPN &copy);
    RPN &operator=(const RPN &source);
    ~RPN();

    void    calculate_RPN(std::string &data);
};

#endif