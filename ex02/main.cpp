#include "PmergeMe.hpp"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Error: incorrect number of elements\n";
        return 1;
    }
    std::string user_input = argv[1];
    try {
        Alg alg_instance(user_input);
        alg_instance.sort_vector_seq();

        alg_instance.print_result();
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}