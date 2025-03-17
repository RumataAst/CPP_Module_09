#include "PmergeMe.hpp"

Alg::Alg(std::string &number_seq) : vector_time(0), deque_time(0), user_input(number_seq) {
    static const int arr[] = { 2, 4, 10, 20, 42, 84, 170, 340, 682, 1364, 2730, 5460, 10922};
   
    pass_to_containers(number_seq);
    jacobstahl_seq(arr< arr + sizeof(arr) / sizeof(arr[0]));
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
        if (std::find(vector_seq.begin(), vector_seq.end(), number) != vector_seq.end())
            throw DuplicateNumber();
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
