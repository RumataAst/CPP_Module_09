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

std::vector<int> generate_jacobsthal_indices(int n_groups) {
    std::vector<int> jacobsthal_seq;

    jacobsthal_seq.push_back(0);
    jacobsthal_seq.push_back(1);

    // Generate enough terms
    while (jacobsthal_seq.back() < n_groups) {
        int next = jacobsthal_seq[jacobsthal_seq.size() - 1] +
                   2 * jacobsthal_seq[jacobsthal_seq.size() - 2];
        jacobsthal_seq.push_back(next);
    }

    // Skip the first 3, subtract 1 from each to get zero-based group indices
    std::vector<int> adjusted_indices;
    for (size_t i = 3; i < jacobsthal_seq.size(); ++i) {
        adjusted_indices.push_back(jacobsthal_seq[i] - 1);
    }

    // Add the total number of groups to handle the last interval
    adjusted_indices.push_back(n_groups);

    return adjusted_indices;
}


std::vector<int> reorder_groups_by_jacobsthal(const std::vector<int>& pend,
                                    int group_size) {
    int n_groups = pend.size() / group_size;
    std::vector<int> jacob_indices = generate_jacobsthal_indices(n_groups);

    std::vector<int> reordered;

    // Start from first interval
    int prev_index = 0;

    for (size_t idx = 0; idx < jacob_indices.size(); ++idx) {
    int curr_index = jacob_indices[idx];

    // Clamp to the number of groups
    if (curr_index > n_groups)
    curr_index = n_groups;

    // Reverse from curr_index - 1 to prev_index
    for (int g = curr_index - 1; g >= prev_index; --g) {
    int start = g * group_size;
    int end = start + group_size;

    reordered.insert(reordered.end(),
    pend.begin() + start,
    pend.begin() + end);
    }

    prev_index = curr_index;

    if (prev_index >= n_groups)
    break;
    }

    return reordered;
}



// Binary insertion: Insert a whole group based on the last element of the group
void binary_insert(std::vector<int>& main_seq, const std::vector<int>& group) {
    size_t left = 0;
    size_t right = main_seq.size() / group.size();  // Number of groups in main_seq
    
    int group_last = group[group.size() - 1];  // last element of the group
    
    // Perform binary search to find the correct position based on the last element of the group
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        int main_seq_last = main_seq[mid * group.size() + group.size() - 1];  // last element of group in main_seq
        
        if (main_seq_last < group_last) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    // Insert the entire group at the found position
    main_seq.insert(main_seq.begin() + left * group.size(), group.begin(), group.end());
}

int binary_search_insert_index(const std::vector<int>& main_seq,
                            const std::vector<int>& group,
                            int right_bound,
                            int group_size) {

    int left = 0;
    int right = right_bound;

    int group_last = group[group_size - 1];  // last element of the group to be inserted

    // Binary search to find the correct insertion point
    while (left < right) {
    int mid = left + (right - left) / 2;
    int main_seq_last = main_seq[mid * group_size + group_size - 1];  // last element of the group at mid

    if (main_seq_last < group_last) {
    left = mid + 1;  // b is bigger, move to the right half
    } else {
    right = mid;  // a is bigger or equal, move to the left half
    }
    }
    return left;
}

void     Alg::sort_vector_seq() {
    int number_swaps = 0;
    int number_compare = 0;

    size_t vector_size = vector_seq.size();
    // std::cout << "Initial Vector:\n";
    // print_vector(vector_seq);

    size_t last1 = 0;
    size_t last2 = 0;

    size_t max_power_of_2 = 1;
    while (max_power_of_2 * 2 <= vector_size) {
        max_power_of_2 *= 2;
    }

    for (size_t i = 0; i + 1 < vector_size; i += 2) {
        if (vector_seq[i] > vector_seq[i + 1]) {
            std::swap(vector_seq[i], vector_seq[i + 1]);
            number_swaps++;
        }
        number_compare++;
    }

    // std::cout << "After first step:\n";
    // print_vector(vector_seq);

    for (size_t number_of_groups = max_power_of_2; number_of_groups >= 2; number_of_groups /= 2) {
        for (size_t i = 0; i + number_of_groups * 2 - 1 < vector_size; i += number_of_groups * 2) {
            last1 = i + number_of_groups - 1;
            last2 = i + 2 * number_of_groups - 1;

            if (vector_seq[last1] > vector_seq[last2]) {
                for (size_t j = 0; j < number_of_groups; ++j) {
                    std::swap(vector_seq[i + j], vector_seq[i + j + number_of_groups]);
                    number_swaps++;
                }
            }
            number_compare++;
        }
        // std::cout << "After initial phase\n";
        // print_vector(vector_seq);
    }



    // std::cout << "After initial comp\n";
    // print_vector(vector_seq);


    std::vector<int>    main_seq;
    std::vector<int>    pend;
    std::vector<int>    odd;

    size_t group_size = max_power_of_2 / 4;  // Start from the largest group size
    int Number_of_steps = 0;
    while (group_size >= 1) {
        Number_of_steps++;
        // std::cout << "Number of steps : " << Number_of_steps << std::endl;
        std::cout << "\nGroup_size : " << group_size << std::endl;

        size_t num_groups = vector_size / group_size;
    
        // The first group always goes to main_seq
        for (size_t j = 0; j < group_size; j++) {
            main_seq.push_back(vector_seq[j]);
        }
    
        // Start alternating from the second group
        for (size_t i = 1; i < num_groups; i++) {
            size_t group_start = i * group_size;
            size_t group_end = group_start + group_size - 1;
        
            // Check if it's the last group
            if (i == num_groups - 1) {
                // Last group goes to odd
                for (size_t j = group_start; j <= group_end; j++) {
                    odd.push_back(vector_seq[j]);
                }
                
                // If there are any remaining elements after the last group
                size_t remaining_start = group_end + 1;
                if (remaining_start < vector_seq.size()) {
                    for (size_t j = remaining_start; j < vector_seq.size(); j++) {
                        main_seq.push_back(vector_seq[j]);
                    }
                }
            } else if (i % 2 == 1) {
                // Odd-indexed groups go to main_seq
                for (size_t j = group_start; j <= group_end; j++) {
                    main_seq.push_back(vector_seq[j]);
                }
            } else if (i % 2 == 0) {
                // Even-indexed groups go to pend
                for (size_t j = group_start; j <= group_end; j++) {
                    pend.push_back(vector_seq[j]);
                }
            }
        }
        std::cout << "Initial vector_seq\n";
        print_vector(vector_seq);
        std::cout << "Main_seq before binary\n";
        print_vector(main_seq);
        std::cout << "Pend before binary\n";
        print_vector(pend);
        std::cout << "Odd before binary\n";
        print_vector(odd);


        std::vector<int> reordered_groups = reorder_groups_by_jacobsthal(pend, group_size);

        // std::cout << "\njacobsthal_seq\n";
        // print_vector(jacobsthal_seq);

        std::cout << "reordered_groups\n";
        print_vector(reordered_groups);
        // Reorder groups based on Jacobsthal sequence and perform binary insertion


        std::vector<int>    main_seq_original = main_seq;
        for (size_t p = 0; p < (reordered_groups.size()) / group_size; ++p) {
            std::vector<int> group(reordered_groups.begin() + p * group_size, reordered_groups.begin() + (p + 1) * group_size);
    
            // Determine the original position of the first element in the group
            int original_index = p;  // Assuming the group corresponds to the p-th element in pend
            int right_bound = std::distance(main_seq_original.begin(),
                                            std::find(main_seq_original.begin(), main_seq_original.end(), original_index));
    
            // Calculate the insertion index using the optimized right_bound
            int insert_index = binary_search_insert_index(main_seq, group, right_bound, group_size);
    
            // Insert the group into main_seq
            main_seq.insert(main_seq.begin() + insert_index * group_size, group.begin(), group.end());
        }

        std::cout << "Main_seq after insert Pend\n";
        print_vector(main_seq);
    
        // Perform binary insertion for all groups in `odd` based on the comparison with the last element of `main_seq`
        for (size_t p = 0; p < odd.size() / group_size; ++p) {
            std::vector<int> group(odd.begin() + p * group_size, odd.begin() + (p + 1) * group_size);
            binary_insert(main_seq, group);
        }
        std::cout << "Main_seq after insert Odd\n";
        print_vector(main_seq);
        // Update vector_seq to be the updated main_seq
        vector_seq = main_seq;


        // std::cout << "Pend\n";
        // print_vector(pend);
        // std::cout << "Odd\n";
        // print_vector(odd);
        // std::cout << "Main_seq after binary\n";
        // print_vector(main_seq);
                

        // After binary insertion, clear pend
        odd.clear();
        pend.clear();
        main_seq.clear();
        
        // vector_size -= num_groups * group_size;  // Reduce vector_size accordingly
        group_size /= 2;  // Move to the next smaller group size

        // std::cout << "Vector_seq after main\n";
        // print_vector(vector_seq);
    }



    std::cout << "Vector_seq\n";
    print_vector(vector_seq);


    // std::cout << "end of last element of first is " << max_power_of_2 / 2 - 1 
    //             << " and the last element of secodn is "<< max_power_of_2 - 1 << std::endl;
    // std::cout << "After last step: last1 is " << last1 << " last2 is " << last2 << std::endl;
    // std::cout << "Total swaps: " << number_swaps << std::endl;
    // std::cout << "Total comp: " << number_compare << std::endl;
}
