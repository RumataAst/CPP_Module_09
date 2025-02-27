#include "RPN.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect number of arguments. Example is ./RPN \"8 9 * 9 - 9 - 9 - 4 - 1 +\"";
        return 1;
    }
    std::string stringRPN = argv[1];
    RPN         rpn;

    rpn.calculate_RPN(stringRPN);
    return 0;
}