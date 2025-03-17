#include "PmergeMe.hpp"


int main(int argc, char *argv[]) {
    std::string user_input;
    if (argc < 2) {
        std::cerr << "Error: add numbers\n";
        return 1;
    }
    else if (argc == 2)
        user_input = argv[1];
    else {
        for (int i = 1; i < argc; ++i) {
            user_input += argv[i];
            user_input += " ";
        }
    }
    try {
        Alg alg_instance(user_input);
        alg_instance.sort_vector_seq();

        // alg_instance.print_result();
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void    Alg::print_result() const {
    std::cout << "Before " << user_input << std::endl;
    std::cout << "After to be done\n";
    std::cout << "Vector : ";
    for (std::vector<int>::const_iterator it = vector_seq.begin(); it != vector_seq.end(); ++it) {
        std::cout << *it;
        std::cout << " ";
    }
    std::cout << std::endl;
    std::cout << "Deque : "; 
        for (std::deque<int>::const_iterator it = deque_seq.begin(); it != deque_seq.end(); ++it) {
        std::cout << *it;
        std::cout << " ";
    }
    std::cout << std::endl;
}