#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void    binary_insert(std::vector<int> &main_seq, std::vector<int> &to_be_inserted, int right_index) {
    size_t  group_size = to_be_inserted.size();
    size_t  left_index = 0, mid_index;
    
    int     target = to_be_inserted.back();
    int     main_seq_last;
    size_t  group_start_index, group_end_index;
    
    if (right_index != -1 && right_index <= main_seq.size() / group_size)
        right_index = static_cast<size_t>(std::pow(2, right_index)) - 1;
    else
        right_index = main_seq.size() / group_size;

    while (left_index < right_index) {
        mid_index = left_index + (right_index - left_index) / 2;
        group_start_index = mid_index * group_size;
        group_end_index = group_start_index + group_size - 1;


        if (main_seq_last < group_end_index) {
            left_index = mid_index + 1;
        }
        else {
            right_index = mid_index;
        }
    }

    main_seq.insert(main_seq.begin() + left_index, to_be_inserted.begin(), to_be_inserted.end());

}


int main(void) {
    std::vector<int>    insert_into = {1, 2, 5 ,6};
    std::vector<int>    to_be_insereted = {3 , 4};

    binary_insert(insert_into, to_be_insereted, 2);


    for (std::vector<int>::iterator it = insert_into.begin(); it != insert_into.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}