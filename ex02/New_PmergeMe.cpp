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

// creating from vector_seq b1a1b2a2....bnan     2 new vectors main_seq b1a1a2..an (rest) + pend b2b3...bn
void processGroups(const std::vector<int>& vector_seq, std::vector<int>& main_seq, std::vector<int>& pend, size_t group_size) {
    size_t vector_size = vector_seq.size();
    size_t num_groups = vector_size / group_size;

    // The first group (b1) always goes to main_seq
    for (size_t j = 0; j < group_size; j++) {
        main_seq.push_back(vector_seq[j]);
    }

    // Process groups starting from the second group (group 1)
    for (size_t i = 1; i < num_groups; i++) {
        size_t group_start = i * group_size;
        size_t group_end = group_start + group_size;

        if (i % 2 == 1 ) {
            for (size_t j = group_start; j < group_end; j++) {
                main_seq.push_back(vector_seq[j]);
            }
        } else {
            for (size_t j = group_start; j < group_end; j++) {
                pend.push_back(vector_seq[j]);
            }
        }
    }

    // Handle remaining elements that couldn't form a complete group
    size_t remaining_start = num_groups * group_size;
    if (remaining_start < vector_size) {
        for (size_t j = remaining_start; j < vector_size; j++) {
            main_seq.push_back(vector_seq[j]);
        }
    }
}

void     Alg::sort_vector_seq() {
    int number_swaps = 0;
    size_t vector_size = vector_seq.size();
    size_t max_power_of_2 = 1;


    while (max_power_of_2 * 2 <= vector_size) {
        max_power_of_2 *= 2;
    }

    // First step
    for (size_t number_of_elements = 1; number_of_elements <= max_power_of_2 / 2; number_of_elements *= 2) {
        for (size_t group = 0; group + number_of_elements * 2 - 1 < vector_size; group += number_of_elements * 2) {
            size_t last1 = group + number_of_elements - 1;
            size_t last2 = group + number_of_elements * 2 - 1;
            
            number_compare++;
            if (vector_seq[last1] > vector_seq[last2]) {
                
                for (size_t i = 0; i < number_of_elements; ++i) {
                    std::swap(vector_seq[group + i], vector_seq[group + number_of_elements + i]);
                    number_swaps++;
                }
            }
        }
    }

    size_t group_size = max_power_of_2 / 2;
    if (group_size == 0)
        group_size = 1;

    std::vector<int>    main_seq;
    std::vector<int>    pend;
    std::vector<int>    jacobsthal;
    std::vector<int>    reorderedPend;

    while (group_size >= 1) {
        main_seq.clear();
        pend.clear();
        reorderedPend.clear();

        //creating main_seq pend_seq
        processGroups(vector_seq, main_seq, pend, group_size);

        //creating new order vector to pend based on the JacobsthalSeq
        jacobsthal = generateJacobsthalSequence(pend.size() / group_size);
        reorderedPend = reorderPend(pend, jacobsthal, group_size);
        if (reorderedPend.empty())
            reorderedPend = pend;


            std::vector<int> group;

        // starting with binary insertion
        size_t start = 0;
        size_t group_count = 2;
        size_t group_number = 0;
        size_t index_jacob = 0;
    }
}