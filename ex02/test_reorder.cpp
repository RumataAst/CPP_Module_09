#include <iostream>
#include <algorithm>
#include <vector>


std::vector<int> re_order(std::vector<int> original, int group_size) {
        std::vector<int> jacob_seq;
        jacob_seq.push_back(2);
        jacob_seq.push_back(4);
        jacob_seq.push_back(10);
        jacob_seq.push_back(20);
        jacob_seq.push_back(42);
        jacob_seq.push_back(84);
    std::vector<int> new_vector;

    int previous_limit = 0;

    for (size_t i = 0; i < jacob_seq.size(); ++i) {
        int group_index = jacob_seq[i];

        if (group_index > static_cast<int>(original.size() / group_size)) {
            group_index = original.size() / group_size;
        }

        int start_index = group_index * group_size - group_size;

        for (int index = start_index; index >= previous_limit; index -= group_size) {
            for (int j = 0; j < group_size; ++j) {
                new_vector.push_back(original[index + j]);
            }
        }

        previous_limit = jacob_seq[i] * group_size;
    }

    return new_vector;
}


// std::vector<int> re_order(std::vector<int> original, int group_size) {
//     std::vector<int> jacob_seq;
//     jacob_seq.push_back(2);
//     jacob_seq.push_back(4);
//     jacob_seq.push_back(10);
//     jacob_seq.push_back(20);
//     jacob_seq.push_back(42);
//     jacob_seq.push_back(84);

//     std::vector<int> new_vector;

//     size_t jacob_seq_index = 0;
//     int     original_index = 0;
//     int     previous_value = 0;
//     int     check = 0;
//     for (size_t i = 0; i < jacob_seq.size(); ++i) {
        
//         if (i != 0) {
//             previous_value = jacob_seq[i-1] * group_size;
//         }

//         if (jacob_seq[i] > original.size() / group_size) {
//             if (check == 0) {
//                 original_index = original.size() - group_size;
//                 check = 1;
//             }
//             else 
//                 break;
//         }
//         else {
//             original_index = jacob_seq[i] * group_size - group_size;
//         }
        
//         while (original_index >= previous_value) {
//             int z = original_index;
//             for (size_t i = 0; i < group_size; i++) {
//                 new_vector.push_back(original[z++]);
//             }
//             original_index -= group_size;
//         }
        
//     }
//     return new_vector;
// }

int main(void) {
    std::vector<int> original = {15, 5, 2, 33, 11, 23, 153, 78, 99, 103, 1 , 13};
    std::vector<int> reordered_copy;
    std::vector<int> reordered_copy_two_elem;


    reordered_copy = re_order(original, 1);

    std::cout << "Original " << std::endl;
    for (int i = 0; i < original.size(); ++i){
        std::cout << original[i] << " ";
    }
    std::cout << std::endl;


    std::cout << "Reordered copy " << std::endl;
    for (int i = 0; i < reordered_copy.size(); ++i){
        std::cout << reordered_copy[i] << " ";
    }
    std::cout << std::endl;



    reordered_copy_two_elem = re_order(original, 2);

    std::cout << "Original with 2 elem " << std::endl;
    for (int i = 0; i < original.size(); ++i){
        std::cout << original[i] << " ";
    }
    std::cout << std::endl;


    std::cout << "Reordered copy with 2 elem " << std::endl;
    for (int i = 0; i < reordered_copy_two_elem.size(); ++i){
        std::cout << reordered_copy_two_elem[i] << " ";
    }
    std::cout << std::endl;


    

    std::vector<int> reordered_copy_thour_elem = re_order(original, 4);

    std::cout << "Original with 4 elem " << std::endl;
    for (int i = 0; i < original.size(); ++i){
        std::cout << original[i] << " ";
    }
    std::cout << std::endl;


    for (int i = 0; i < reordered_copy_thour_elem.size(); ++i){
        std::cout << reordered_copy_thour_elem[i] << " ";
    }
    std::cout << std::endl;
}