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

std::vector<int> generateJacobsthalSequence(int size) {
    std::vector<int> jacobsthal;
    
    if (size <= 0)
        return jacobsthal;

    jacobsthal.push_back(2); // J(1) = 2

    if (size == 1)
        return jacobsthal;

    jacobsthal.push_back(4); // J(2) = 4

    int i = 2;
    while (jacobsthal.back() < size) {
        int next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
        jacobsthal.push_back(next);
        ++i;
    }

    return jacobsthal;
}

std::vector<int> reorderPend(const std::vector<int>& pend, const std::vector<int>& jacobsthal, size_t group_size) {
    std::vector<int> reorderedPend;
    if (pend.empty() || group_size == 0) {
        return reorderedPend;
    }

    size_t total_size = pend.size();
    size_t number_of_groups = (total_size + group_size - 1) / group_size;
    size_t prev_group = 0;

    for (size_t i = 0; i < jacobsthal.size(); ++i) {
        int j = jacobsthal[i];
        size_t current_group = static_cast<size_t>(j) - 1; // Convert Jacobsthal 1-based to 0-based group index

        if (current_group >= number_of_groups) {
            continue;
        }

        // Add groups from current_group down to prev_group
        for (int group_idx = current_group; group_idx >= static_cast<int>(prev_group); --group_idx) {
            size_t start = group_idx * group_size;
            size_t end = start + group_size;
            end = std::min(end, total_size);
            for (size_t k = start; k < end; ++k) {
                reorderedPend.push_back(pend[k]);
            }
        }

        prev_group = current_group + 1;
    }

    // Add remaining groups in their natural order
    for (size_t group_idx = prev_group; group_idx < number_of_groups; ++group_idx) {
        size_t start = group_idx * group_size;
        size_t end = start + group_size;
        end = std::min(end, total_size);
        for (size_t k = start; k < end; ++k) {
            reorderedPend.push_back(pend[k]);
        }
    }

    return reorderedPend;
}

size_t binarySearchInsertPosition(const std::vector<int>& vec, int value, size_t left, size_t right) {
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        if (vec[mid] == value) {
            return mid; // Insert at the position of the duplicate
        } else if (vec[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left; // Insert at the correct position to maintain sorted order
}

// Insert odd numbers into `main_seq` in sorted order
void insertOddIntoMain(std::vector<int>& main_seq, const std::vector<int>& odd) {
    for (size_t i = 0; i < odd.size(); ++i) {
        if (odd[i] % 2 != 0) { // Ensure the number is odd
            size_t rightBound = main_seq.empty() ? 0 : main_seq.size() - 1;
            size_t insertPos = binarySearchInsertPosition(main_seq, odd[i], 0, rightBound);
            main_seq.insert(main_seq.begin() + insertPos, odd[i]);
        }
    }
}

void processGroups(const std::vector<int>& vector_seq, std::vector<int>& main_seq, std::vector<int>& pend, std::vector<int>& odd, size_t group_size) {
    size_t vector_size = vector_seq.size();
    size_t num_groups = vector_size / group_size;

    // The first group (group 0) always goes to main_seq
    for (size_t j = 0; j < group_size; j++) {
        main_seq.push_back(vector_seq[j]);
    }

    // Process groups starting from the second group (group 1)
    for (size_t i = 1; i < num_groups; i++) {
        size_t group_start = i * group_size;
        size_t group_end = group_start + group_size;

        if (i == num_groups - 1) {
            // Last group goes to odd
            for (size_t j = group_start; j < group_end; j++) {
                odd.push_back(vector_seq[j]);
            }
        } else if (i % 2 == 1) {
            // Odd iteration index (group 1, 3, ...) go to main_seq
            for (size_t j = group_start; j < group_end; j++) {
                main_seq.push_back(vector_seq[j]);
            }
        } else {
            // Even iteration index (group 2, 4, ...) go to pend
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
    int number_compare = 0;

    size_t vector_size = vector_seq.size();
    size_t max_power_of_2 = 1;

    // Find the maximum power of 2 less than or equal to the vector size
    while (max_power_of_2 * 2 <= vector_size) {
        max_power_of_2 *= 2;
    }

    // std::cout << "Before initial phase\n";
    print_vector(vector_seq);

    for (size_t number_of_elements = 1; number_of_elements <= max_power_of_2 / 2; number_of_elements *= 2) {
        for (size_t group = 0; group + number_of_elements * 2 - 1 < vector_size; group += number_of_elements * 2) {
            size_t last1 = group + number_of_elements - 1; // Last index of the first group
            size_t last2 = group + number_of_elements * 2 - 1; // Last index of the second group
    
            // Compare the last elements of the two groups
            if (vector_seq[last1] > vector_seq[last2]) {
                number_compare++;
                // Swap the two groups
                for (size_t i = 0; i < number_of_elements; ++i) {
                    std::swap(vector_seq[group + i], vector_seq[group + number_of_elements + i]);
                    number_swaps++;
                }
            }
        }
        std::cout << "After initial phase\n";
        print_vector(vector_seq);
    }
    
    //Second step of creating main_seq, ped, odd
    size_t group_size = max_power_of_2 / 4;
    std::vector<int>    main_seq;
    std::vector<int>    pend;
    std::vector<int>    odd;

    while (group_size >= 1) {
        std::cout << "\nGroup_size : " << group_size << std::endl;
        main_seq.clear();
        pend.clear();
        odd.clear();
    
        processGroups(vector_seq, main_seq, pend, odd, group_size);
        
        // Recompute Jacobsthal sequence and reorderedPend after pend is updated.
        std::vector<int> jacobsthal = generateJacobsthalSequence(pend.size());
        std::vector<int> reorderedPend = reorderPend(pend, jacobsthal, group_size);
    
        // std::cout << "Main_seq\n";
        // print_vector(main_seq);
        // std::cout << "Pend\n";
        // print_vector(pend);
        std::cout << "Reordered Pend\n";
        print_vector(reorderedPend);
        // std::cout << "Odd\n";
        // print_vector(odd);
    
        // std::cout << "Jacobsthal\n";
        // print_vector(jacobsthal);


        std::vector<int> group;
        size_t start = 0;
        while (start < reorderedPend.size()) {
            // Clear the group vector to hold the new group of elements
            group.clear();
            // Push elements to the group (make sure not to exceed the group size or vector size)
            for (size_t i = 0; i < group_size && start < reorderedPend.size(); ++i) {
                group.push_back(reorderedPend[start]);
                start++;
            }
            // print_vector(group);
            // Send the group to another function for processing
            insertOddIntoMain(main_seq, group);
        }
        // insertPendIntoMain(main_seq, reorderedPend, jacobsthal);
        insertOddIntoMain(main_seq, odd);
        
        
        group_size /= 2;
    }

    std::cout << "Main_vector\n";
    print_vector(vector_seq);

}