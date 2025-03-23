#include "PmergeMe.hpp"

Alg::Alg(std::string &number_seq) : vector_time(0), deque_time(0), user_input(number_seq), jacobstahl_seq(0) {
   
    pass_to_containers(number_seq);
    generate_jacobstahl();
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
    this->jacobstahl_seq = source.jacobstahl_seq;
    return *this;
}

void    Alg::pass_to_containers(std::string &number_seq) {
    std::stringstream   iss(number_seq);
    int                 number;

    //Additional check for numbers needed;

    while (iss >> number) {
        if (number < 0)
            throw NegativeNumber();
        if (std::find(vector_seq.begin(), vector_seq.end(), number) != vector_seq.end())
            throw DuplicateNumber();
        vector_seq.push_back(number); 
        deque_seq.push_back(number);
    }
}


void    Alg::generate_jacobstahl() {
    jacobstahl_seq.push_back(2);
    jacobstahl_seq.push_back(4);
    jacobstahl_seq.push_back(10);
    jacobstahl_seq.push_back(20);
    jacobstahl_seq.push_back(42);
    jacobstahl_seq.push_back(84);
    jacobstahl_seq.push_back(170);
    jacobstahl_seq.push_back(340);
    jacobstahl_seq.push_back(682);
    jacobstahl_seq.push_back(1364);
    jacobstahl_seq.push_back(2730);
    jacobstahl_seq.push_back(5460);
    jacobstahl_seq.push_back(10922);
    jacobstahl_seq.push_back(21845);
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

std::vector<int> Alg::reorderPend(const std::vector<int>& pend, size_t group_size) {
    std::vector<int> new_vector;

    int     original_index = 0;
    int     previous_value = 0;
    int     check = 0;
    for (size_t i = 0; i < jacobstahl_seq.size(); ++i) {
        
        if (i != 0) {
            previous_value = jacobstahl_seq[i-1] * group_size;
        }

        if (jacobstahl_seq[i] > static_cast<int>(pend.size() / group_size)) {
            if (check == 0) {
                original_index = pend.size() - group_size;
                check = 1;
            }
            else 
                break;
        }
        else {
            original_index = jacobstahl_seq[i] * group_size - group_size;
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

void Alg::binary_insert_index(std::vector<int>& main_seq, const std::vector<int>& group, int &number_compare, int right_index) {
    size_t left = 0;
    size_t right = 0;

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

        if (group_end_index < main_seq.size()) {
            main_seq_last = main_seq[group_end_index];
        }

        number_compare++;
        if (main_seq_last < group_last) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    main_seq.insert(main_seq.begin() + left * group.size(), group.begin(), group.end());
}


// creating from vector_seq b1a1b2a2....bnan     2 new vectors main_seq b1a1a2..an (rest) + pend b2b3...bn
void Alg::processGroups(const std::vector<int>& vector_seq, std::vector<int>& main_seq, std::vector<int>& pend, size_t group_size) {
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

void    Alg::sorting(std::vector<int> &vector_seq, size_t max_power_of_2, int &number_compare) {
    size_t vector_size = vector_seq.size();
    for (size_t number_of_elements = 1; number_of_elements <= max_power_of_2 / 2; number_of_elements *= 2) {
        for (size_t group = 0; group + number_of_elements * 2 - 1 < vector_size; group += number_of_elements * 2) {
            size_t last1 = group + number_of_elements - 1;
            size_t last2 = group + number_of_elements * 2 - 1;
            
            number_compare++;
            if (vector_seq[last1] > vector_seq[last2]) {
                
                for (size_t i = 0; i < number_of_elements; ++i) {
                    std::swap(vector_seq[group + i], vector_seq[group + number_of_elements + i]);
                }
            }
        }
    }
}

void    Alg::merging(std::vector<int> &vector_seq, size_t group_size, int &number_compare) {
    std::vector<int>    main_seq;
    std::vector<int>    pend;
    std::vector<int>    reorderedPend;

    //creating main_seq pend_seq
    processGroups(vector_seq, main_seq, pend, group_size);
    if (pend.empty())
        return ;
    
    //creating new reorderedPend vector based on the pend and jacobstahl_seqSeq
    reorderedPend = reorderPend(pend, group_size);
    if (reorderedPend.empty())
        reorderedPend = pend;

    // group that will be passed from reorderedPend to main_seq
    std::vector<int> group;

    // starting with binary insertion
    size_t start = 0;
    size_t group_count = 2;
    size_t group_number = 0;
    size_t index_jacob = 0;

    int right_index = 0;

    while (start <= reorderedPend.size() - 1) {
        group.clear();
        for (size_t i = 0; i < group_size && start < reorderedPend.size(); ++i) {
            group.push_back(reorderedPend[start]);
            start++;
        }

        if (static_cast<int>(group_number) >= jacobstahl_seq[index_jacob]) {
                index_jacob++;
                group_count++;
            }
        group_number++;

        right_index = group_count;
        if (group_count > 31)
            right_index = -1;

        binary_insert_index(main_seq, group, number_compare, right_index);
    }
    vector_seq = main_seq;
}

void     Alg::sort_vector_seq() {
    int number_compare = 0;
    vector_time = std::clock();
    size_t vector_size = vector_seq.size();
    size_t max_power_of_2 = 1;


    while (max_power_of_2 * 2 <= vector_size) {
        max_power_of_2 *= 2;
    }

    // First step sorting inside the vector
    sorting(vector_seq, max_power_of_2,number_compare);

    size_t group_size = max_power_of_2 / 2;
    if (group_size == 0)
        group_size = 1;

    // Second step, creating vectors main and pend and then insering groups from pend in the jacobsthal_seq to main
    while (group_size >= 1) {
        merging(vector_seq, group_size, number_compare);
        group_size /= 2;
    }

    
    std::cout << "Final sequence\n";
    print_vector(vector_seq);
    std::cout << "Final number of comparision " << number_compare << std::endl;


    for (size_t i = 1; i < vector_seq.size() ;++i) {
        if (vector_seq[i-1] > vector_seq[i]){
            std::cout << "\nNot really sorted " << vector_seq[i - 1] << " and " << vector_seq[i] << std::endl;    
        }
    }
    std::cout << "Time needed is " << (double)(std::clock() - vector_time) / CLOCKS_PER_SEC * 1000000 << " us(micro seconds)"<< std::endl;
}