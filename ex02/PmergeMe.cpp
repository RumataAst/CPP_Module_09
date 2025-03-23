#include "PmergeMe.hpp"
#include <climits>
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


std::vector<int> generateJacobsthalSequence(int size) {
    std::vector<int>    jacob_original;
    std::vector<int>    jacob_adj;
    int                 last_value = 0;

    if (size < 2)
        return jacob_adj;
    else if (size >= 2 && size <= 3) {
        jacob_adj.push_back(2);
        return jacob_adj;
    }

    jacob_original.push_back(0);
    jacob_original.push_back(1);

    for (int i = 2; last_value < size; ++i) {
        last_value = jacob_original[i - 1] + 2 * jacob_original[i - 2];
        jacob_original.push_back(last_value);
        if (last_value >= 3 && last_value < size)
            jacob_adj.push_back(last_value - 1);
    }
    (void)size;

    jacob_adj.push_back(2);
    jacob_adj.push_back(4);
    jacob_adj.push_back(10);
    jacob_adj.push_back(20);
    jacob_adj.push_back(42);
    jacob_adj.push_back(84);
    jacob_adj.push_back(170);
    jacob_adj.push_back(340);
    jacob_adj.push_back(682);
    jacob_adj.push_back(1364);
    jacob_adj.push_back(2730);
    jacob_adj.push_back(5460);
    jacob_adj.push_back(10922);
    jacob_adj.push_back(21845);


    return jacob_adj;
}


std::vector<int> reorderPend(const std::vector<int>& pend, const std::vector<int>& jacobsthal, size_t group_size) {
    std::vector<int> new_vector;

    int     original_index = 0;
    int     previous_value = 0;
    int     check = 0;
    for (size_t i = 0; i < jacobsthal.size(); ++i) {
        
        if (i != 0) {
            previous_value = jacobsthal[i-1] * group_size;
        }

        if (jacobsthal[i] > static_cast<int>(pend.size() / group_size)) {
            if (check == 0) {
                original_index = pend.size() - group_size;
                check = 1;
            }
            else 
                break;
        }
        else {
            original_index = jacobsthal[i] * group_size - group_size;
        }
        
        while (original_index >= previous_value) {
            int z = original_index;
            for (size_t i = 0; i < group_size; i++) {
                new_vector.push_back(pend[z++]);
            }
            original_index -= group_size;
        }
        
    }
    return new_vector;
}

void processGroups(const std::vector<int>& vector_seq, std::vector<int>& main_seq, std::vector<int>& pend, size_t group_size) {
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

void binary_insert_index(std::vector<int>& main_seq, const std::vector<int>& group, int &number_compare, int right_index) {
    size_t left = 0;
    size_t right = 0;

    // std::cout << "Right index is " << right_index << std::endl;

    // Calculate right boundary of search space
    if (right_index != -1)
        right = static_cast<size_t>(std::pow(2, right_index)) - 1;
    else
        right = main_seq.size() / group.size();

    // Clamp right to avoid going out of bounds
    if (right > main_seq.size() / group.size()) {
        right = main_seq.size() / group.size();
    }

    int group_last = group.back();
    int main_seq_last = 0;

    // Binary search on groups
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        size_t group_start_index = mid * group.size();
        size_t group_end_index = group_start_index + group.size() - 1;

        // Ensure we don't go out of bounds
        if (group_end_index < main_seq.size()) {
            main_seq_last = main_seq[group_end_index];
        } else {
            // Out of bounds: pretend it's "infinity"
            main_seq_last = INT_MAX;
        }

        number_compare++;
        
        if (main_seq_last < group_last) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    // Calculate insertion position, clamping to the end if necessary
    // size_t insert_pos = std::min(left * group.size(), main_seq.size());

    main_seq.insert(main_seq.begin() + left * group.size(), group.begin(), group.end());
}

void     Alg::sort_vector_seq() {
    int number_swaps = 0;
    int number_compare = 0;

    size_t vector_size = vector_seq.size();
    size_t max_power_of_2 = 1;


    // std::cout << "Initial Vector: ";
    // print_vector(vector_seq);


    // Find the maximum power of 2 less than or equal to the vector size
    while (max_power_of_2 * 2 <= vector_size) {
        max_power_of_2 *= 2;
    }

    for (size_t number_of_elements = 1; number_of_elements <= max_power_of_2 / 2; number_of_elements *= 2) {
        for (size_t group = 0; group + number_of_elements * 2 - 1 < vector_size; group += number_of_elements * 2) {
            size_t last1 = group + number_of_elements - 1; // Last index of the first group
            size_t last2 = group + number_of_elements * 2 - 1; // Last index of the second group
            
            // Compare the last elements of the two groups
            number_compare++;
            if (vector_seq[last1] > vector_seq[last2]) {
                
                for (size_t i = 0; i < number_of_elements; ++i) {
                    std::swap(vector_seq[group + i], vector_seq[group + number_of_elements + i]);
                    number_swaps++;
                }
            }
        }
        // std::cout << "Group with : " << number_of_elements << " elements" << std::endl;
        // print_vector(vector_seq);
    }
    
    size_t group_size = max_power_of_2 / 2;
    if (group_size == 0)
        group_size = 1;

    std::vector<int>    main_seq;
    std::vector<int>    pend;
    std::vector<int>    jacobsthal;
    std::vector<int>    reorderedPend;

    while (group_size >= 1) {
        // std::cout << "\nGroup_size : " << group_size << std::endl;
        main_seq.clear();
        pend.clear();
        jacobsthal.clear();
        reorderedPend.clear();

        processGroups(vector_seq, main_seq, pend, group_size);
        
        // Recompute Jacobsthal sequence and reorderedPend after pend is updated.
        jacobsthal = generateJacobsthalSequence(pend.size() / group_size);
        reorderedPend = reorderPend(pend, jacobsthal, group_size);
        if (reorderedPend.empty())
            reorderedPend = pend;
            

            // Debugging 
        // std::cout << std::endl;
        // std::cout << "\n\nGroup_size : " << group_size << std::endl;



        // std::cout << "Pend: ";
        // print_vector(pend);

        // std::cout << "reorderedPend: ";
        // print_vector(reorderedPend);


        // std::cout << "Jacob:  ";
        // print_vector(jacobsthal);
        std::vector<int> group;


        size_t start = 0;
        size_t group_count = 2;
        size_t group_number = 0;
        size_t index_jacob = 0;


                    
        // std::cout << "Vector_seq:  ";
        // print_vector(vector_seq);

        if (!reorderedPend.empty()) {
            int right_index = 0;

            while (start <= reorderedPend.size() - 1) {

            
            group.clear();
            for (size_t i = 0; i < group_size && start < reorderedPend.size(); ++i) {
                group.push_back(reorderedPend[start]);
                start++;
            }

            // std::cout << "\nGroup to be inserted is ";
            // print_vector(group);
    
            if (!jacobsthal.empty()) {
                if (static_cast<int>(group_number) >= jacobsthal[index_jacob]) {
                    index_jacob++;
                    group_count++;
                }
                group_number++;
            }


            // std::cout << "Index jacob is " << index_jacob << " vs " << jacobsthal.size() - 1 << std::endl;

            right_index = group_count;


            if (group_count > 31)
                right_index = -1;

            // if (group_count > 31
            //     || (group_number == (reorderedPend.size() / group_size) && 
            //     ((vector_seq.size() / group_size) % 2 == 1)))
            //     right_index = -1;



            // std::cout << "Right index is " << right_index << std::endl;
            // std::cout << "Group number is " << group_number << " out of " << reorderedPend.size() / group_size << std::endl;
            // std::cout << "Index jacob is " << index_jacob << std::endl;


            // std::cout << "Main_seq before insert:  ";
            print_vector(main_seq);
            binary_insert_index(main_seq, group, number_compare, right_index);
            // std::cout << "Main_seq after insert:  ";
            // print_vector(main_seq);
        }
    }

        group_size /= 2;
        vector_seq = main_seq;
    }
    
    std::cout << "Final sequence\n";
    print_vector(vector_seq);
    std::cout << "Final number of comparision " << number_compare << std::endl;


    for (size_t i = 1; i < vector_seq.size() ;++i) {
        if (vector_seq[i-1] > vector_seq[i]){
            std::cout << "\nNot really sorted " << vector_seq[i - 1] << " and " << vector_seq[i] << std::endl;    
        }
    }
}