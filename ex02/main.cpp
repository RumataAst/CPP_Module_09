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
        MergeSorter alg_instance(user_input);
        alg_instance.sort_container_seq("vector");
        alg_instance.sort_container_seq("deque");

        alg_instance.print_result();
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}


