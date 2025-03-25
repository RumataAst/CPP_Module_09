#include "PmergeMe.hpp"

MergeSorter::MergeSorter(std::string &number_seq) : vector_time(0), deque_time(0), user_input(number_seq), jacobstahl_seq(0) {
   
    pass_to_containers(number_seq);
    generate_jacobstahl();
}

MergeSorter::~MergeSorter() {}

MergeSorter::MergeSorter(const MergeSorter &copy) : vector_seq(copy.vector_seq), deque_seq(copy.deque_seq),
                            vector_time(copy.vector_time), deque_time(copy.deque_time),
                            user_input(copy.user_input){

}

MergeSorter &MergeSorter::operator=(const MergeSorter &source) {
    if (this == &source) {
        return *this;
    }
    this->vector_time = source.vector_time;
    this->deque_time = source.deque_time;
    this->user_input = source.user_input;
    this->deque_seq = source.deque_seq;
    this->vector_seq = source.vector_seq;
    this->jacobstahl_seq = source.jacobstahl_seq;
    return *this;
}

void    MergeSorter::pass_to_containers(std::string &number_seq) {
    std::stringstream   iss(number_seq);
    int                 number;

    //Additional check for numbers needed;

    if (number_seq.find_first_not_of(' ') == std::string::npos)
        throw NotANumber();
    for (size_t i = 0; i < number_seq.size(); i++) {
        if ((number_seq[i] < 48 || number_seq[i] > 57) && number_seq[i] != 32)
            throw NotANumber();
    }

    while (iss >> number) {
        if (number < 0)
            throw NegativeNumber();
        if (std::find(vector_seq.begin(), vector_seq.end(), number) != vector_seq.end())
            throw DuplicateNumber();
        vector_seq.push_back(number); 
        deque_seq.push_back(number);
    }
}


void    MergeSorter::generate_jacobstahl() {
    static const int arr[] = {2, 4, 10, 20, 42, 84, 170, 340, 682, 1364, 2730, 5460, 10922, 21844};
    jacobstahl_seq.assign(arr, arr + 14);
}

void    MergeSorter::print_result() const {
    std::cout << "Before :" << user_input << std::endl;
    std::cout << "After :\n";
    std::cout << "Vector : ";
    for (std::vector<int>::const_iterator it = vector_seq.begin(); it != vector_seq.end(); ++it) {
        std::cout << *it;
        std::cout << " ";
    }
    std::cout << std::endl;
    std::cout << "Time in us (micro seconds) is " << vector_time << std::endl;
    for (std::vector<int>::const_iterator it = vector_seq.begin() + 1; it != vector_seq.end(); ++it) {
        if (*it < *(it - 1)){
            std::cout << "Vector is not sorted\n";
            break;
        }
    }

    std::cout << "Deque : "; 
    for (std::deque<int>::const_iterator it = deque_seq.begin(); it != deque_seq.end(); ++it) {
        std::cout << *it;
        std::cout << " ";
    }
    std::cout << std::endl;
    std::cout << "Time in us (micro seconds) is " << deque_time << std::endl;

    for (std::deque<int>::const_iterator it = deque_seq.begin() + 1; it != deque_seq.end(); ++it) {
        if (*it < *(it - 1)){
            std::cout << "Deque is not sorted\n";
            break;
        }
    }
}


void MergeSorter::sort_container_seq(std::string type_container) {
    int number_compare = 0;
    size_t max_power_of_2 = 1;

    // Choose container based on type
    std::vector<int>& current_vector = vector_seq;
    std::deque<int>& current_deque = deque_seq;

    size_t container_size = 0;

    // Time tracking
    std::clock_t start_time;
    double elapsed_time;

    if (type_container == "vector") {
        container_size = current_vector.size();
        start_time = std::clock();
    } else if (type_container == "deque") {
        container_size = current_deque.size();
        start_time = std::clock();
    } else {
        std::cerr << "Unknown container type: " << type_container << std::endl;
        return;
    }

    while (max_power_of_2 * 2 <= container_size) {
        max_power_of_2 *= 2;
    }

    // Sort
    if (type_container == "vector") {
        sorting(current_vector, max_power_of_2, number_compare);
    } else {
        sorting(current_deque, max_power_of_2, number_compare);
    }

    // Merge
    size_t group_size = max_power_of_2 / 2;
    if (group_size == 0)
        group_size = 1;

    while (group_size >= 1) {
        if (type_container == "vector") {
            merging(current_vector, group_size, number_compare);
        } else {
            merging(current_deque, group_size, number_compare);
        }
        group_size /= 2;
    }

    // Time calculation
    elapsed_time = (double)(std::clock() - start_time) / CLOCKS_PER_SEC * 1000000;

    if (type_container == "vector") {
        vector_time = elapsed_time;
    } else {
        deque_time = elapsed_time;
    }

    // Debugging purposes
    // std::cout << "Number of comparisons for " << type_container << " is " << number_compare << std::endl;
}
