#include "PmergeMe.hpp"

// throw error if negative number is in string
Alg::Alg(std::string &number_seq) : vector_time(0), deque_time(0), user_input(number_seq) {
        pass_to_containers(number_seq);
}

Alg::~Alg() {}

Alg::Alg(const Alg &copy) : vector_seq(copy.vector_seq), deque_seq(copy.deque_seq),
                            vector_time(copy.vector_time), deque_time(copy.deque_time),
                            user_input(copy.user_input){

}

Alg &Alg::operator=(const Alg &source) {
    if (this == &source) {
        return *this;
    }
    this->vector_time = source.vector_time;
    this->deque_time = source.deque_time;
    this->user_input = source.user_input;
    this->deque_seq = source.deque_seq;
    this->vector_seq = source.vector_seq;
    return *this;
}

void    Alg::pass_to_containers(std::string &number_seq) {
    std::stringstream   iss(number_seq);
    int                 number;

    while (iss >> number) {
        if (number < 0)
            throw NegativeNumber();
        vector_seq.push_back(number); 
        deque_seq.push_back(number);
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

void     Alg::sort_vector_seq() {
    int number_swaps = 0;
    size_t vector_size = vector_seq.size();

    std::cout << "Initial Vector:\n";
    print_vector(vector_seq);

    // First step: Swap adjacent elements
    for (size_t i = 0; i + 1 < vector_size; i += 2) {
        if (vector_seq[i] > vector_seq[i + 1]) {
            std::swap(vector_seq[i], vector_seq[i + 1]);
            number_swaps++;
        }
    }

    std::cout << "After first step:\n";
    print_vector(vector_seq);

    size_t max_power_of_2 = 1;
    while (max_power_of_2 * 2 <= vector_size) {
        max_power_of_2 *= 2;
    }

    size_t last1 = 0;
    size_t last2 = 0;
    for (size_t group_size = max_power_of_2; group_size >= 2; group_size /= 2) {
        for (size_t i = 0; i + group_size * 2 - 1 < vector_size; i += group_size * 2) {
            last1 = i + group_size - 1;
            last2 = i + 2 * group_size - 1;

            if (vector_seq[last1] > vector_seq[last2]) {
                for (size_t j = 0; j < group_size; ++j) {
                    std::swap(vector_seq[i + j], vector_seq[i + j + group_size]);
                    number_swaps++;
                }
            }
        }
        print_vector(vector_seq);
    }
    std::cout << "end of last element of first is " << max_power_of_2 / 2 - 1 
                << " and the last element of secodn is "<< max_power_of_2 - 1 << std::endl;
    std::cout << "After last step: last1 is " << last1 << " last2 is " << last2 << std::endl;
    std::cout << "Total swaps: " << number_swaps << std::endl;
}
