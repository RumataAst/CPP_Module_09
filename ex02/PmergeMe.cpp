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
    std::vector<int> jacobsthal_normal;
    std::vector<int> jacobsthal;

    if (size <= 0 || size == 1) 
        return jacobsthal_normal;

    jacobsthal_normal.push_back(0);  // J(0) = 0

    jacobsthal_normal.push_back(1);  // J(1) = 1
    for (int i = 2; i < size; ++i) {
        jacobsthal_normal.push_back(jacobsthal_normal[i - 1] + 2 * jacobsthal_normal[i - 2]);
    }

    for (size_t i = 3; i < jacobsthal_normal.size(); ++i) {
        jacobsthal.push_back(jacobsthal_normal[i] - 1);
    }    
    return jacobsthal;
}

std::vector<int> reorderPend(const std::vector<int>& pend, const std::vector<int>& jacobsthal, size_t group_size) {
    std::vector<int> reorderedPend;
    if (pend.empty() || group_size == 0 || jacobsthal.empty()) {
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

void binary_insert_index(std::vector<int>& main_seq, const std::vector<int>& group, int &number_compare, int group_count) {
    size_t left = 0;
    size_t right = 0;
    if (group_count != 0)
        right = pow(2, group_count + 1) - 1;
    if (group_count == 0 || right >= main_seq.size() / group.size()) 
        right = main_seq.size() / group.size(); 

    int group_last = group[group.size() - 1];
    
    // Perform binary search to find the correct position based on the last element of the group
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        int main_seq_last = main_seq[mid * group.size() + group.size() - 1];  // last element of group in main_seq
        
        if (main_seq_last < group_last) {
            left = mid + 1;
        } else {
            right = mid;
        }
        number_compare++;
    }

    // Insert the entire group at the found position
    main_seq.insert(main_seq.begin() + left * group.size(), group.begin(), group.end());
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

    std::cout << "Before initial phase\n";
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
    }
    
    size_t group_size = max_power_of_2 / 4;
    std::vector<int>    main_seq;
    std::vector<int>    pend;
    std::vector<int>    odd;

    while (group_size >= 1) {
        // std::cout << "\nGroup_size : " << group_size << std::endl;
        main_seq.clear();
        pend.clear();
        odd.clear();
    
        processGroups(vector_seq, main_seq, pend, odd, group_size);

        // Recompute Jacobsthal sequence and reorderedPend after pend is updated.
        std::vector<int> jacobsthal = generateJacobsthalSequence(pend.size() / group_size);
        std::vector<int> reorderedPend = reorderPend(pend, jacobsthal, group_size);
        if (reorderedPend.empty())
            reorderedPend = pend;

        std::cout << "jacobsthal\n";
        print_vector(jacobsthal);

        std::vector<int> group;

        size_t start = 0;
        std::vector<int> original_main_seq = vector_seq;
        size_t group_count = 0;
        while (start <= reorderedPend.size() - 1) {
            group.clear();
            for (size_t i = 0; i < group_size && start < reorderedPend.size(); ++i) {
                group.push_back(reorderedPend[start]);
                start++;
            }
            group_count++;

            binary_insert_index(main_seq, group, number_compare, group_count);

        }
        binary_insert_index(main_seq, odd, number_compare, 0);
        
        group_size /= 2;
        vector_seq = main_seq;
    }
    
    std::cout << "Main_vector\n";
    print_vector(vector_seq);
    std::cout << "Number of comparision " << number_compare << std::endl;
}