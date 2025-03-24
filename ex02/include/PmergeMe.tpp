#include <PmergeMe.hpp>


template <typename Container>
Container MergeSorter::reorderPend(const Container& pend, size_t group_size) {
    Container new_pend;

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
                new_pend.push_back(pend[z++]);
            }
            original_index -= group_size;
        }
        
    }
    return new_pend;
}

template <typename Container>
void MergeSorter::binary_insert_index(Container &main_seq, const Container &group, int &number_compare, int right_index) {
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


// creating from container_seq b1a1b2a2....bnan     2 new vectors main_seq b1a1a2..an (rest) + pend b2b3...bn
template <typename Container>
void MergeSorter::processGroups(const Container &container_seq, Container &main_seq, Container &pend, size_t group_size) {
    size_t container_size = container_seq.size();
    size_t num_groups = container_size / group_size;

    // The first group (b1) always goes to main_seq
    for (size_t j = 0; j < group_size; j++) {
        main_seq.push_back(container_seq[j]);
    }

    // Process groups starting from the second group (group 1)
    for (size_t i = 1; i < num_groups; i++) {
        size_t group_start = i * group_size;
        size_t group_end = group_start + group_size;

        if (i % 2 == 1 ) {
            for (size_t j = group_start; j < group_end; j++) {
                main_seq.push_back(container_seq[j]);
            }
        } else {
            for (size_t j = group_start; j < group_end; j++) {
                pend.push_back(container_seq[j]);
            }
        }
    }

    // Handle remaining elements that couldn't form a complete group
    size_t remaining_start = num_groups * group_size;
    if (remaining_start < container_size) {
        for (size_t j = remaining_start; j < container_size; j++) {
            main_seq.push_back(container_seq[j]);
        }
    }
}

template <typename Container>
void    MergeSorter::sorting(Container &container_seq, size_t max_power_of_2, int &number_compare) {
    size_t container_size = container_seq.size();
    for (size_t number_of_elements = 1; number_of_elements <= max_power_of_2 / 2; number_of_elements *= 2) {
        for (size_t group = 0; group + number_of_elements * 2 - 1 < container_size; group += number_of_elements * 2) {
            size_t last1 = group + number_of_elements - 1;
            size_t last2 = group + number_of_elements * 2 - 1;
            
            number_compare++;
            if (container_seq[last1] > container_seq[last2]) {
                
                for (size_t i = 0; i < number_of_elements; ++i) {
                    std::swap(container_seq[group + i], container_seq[group + number_of_elements + i]);
                }
            }
        }
    }
}

template <typename Container>
void    MergeSorter::merging(Container &container_seq, size_t group_size, int &number_compare) {
    Container    main_seq;
    Container    pend;
    Container    reorderedPend;

    //creating main_seq pend_seq
    processGroups(container_seq, main_seq, pend, group_size);
    if (pend.empty())
        return ;
    
    //creating new reorderedPend vector based on the pend and jacobstahl_seqSeq
    reorderedPend = reorderPend(pend, group_size);
    if (reorderedPend.empty())
        reorderedPend = pend;

    // group that will be passed from reorderedPend to main_seq
    Container group;

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
    container_seq = main_seq;
}