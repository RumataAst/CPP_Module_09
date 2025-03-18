#include <iostream>
#include <algorithm>
#include <vector>


std::vector<int> re_order(std::vector<int> original) {
    std::vector<int> jacob_seq;
    jacob_seq.push_back(2);
    jacob_seq.push_back(4);
    jacob_seq.push_back(10);
    jacob_seq.push_back(20);
    jacob_seq.push_back(42);
    jacob_seq.push_back(84);

    std::vector<int> new_vector;

    size_t jacob_seq_index = 0;
    int     original_index = 0;
    int     previous_value = 0;
    int     check = 0;
    for (size_t i = 0; i < jacob_seq.size(); ++i) {
        
        if (i != 0) {
            previous_value = jacob_seq[i-1];
        }

        if (jacob_seq[i] > original.size()) {
            if (check == 0) {
                original_index = original.size() - 1;
                check = 1;
            }
            else 
                break;
        }
        else {
            original_index = jacob_seq[i] - 1;
        }

        while (original_index >= previous_value) {
            new_vector.push_back(original[original_index]);
            original_index--;
        }
        
    }
    return new_vector;
}

int main(void) {
    std::vector<int> original = {15, 5, 2, 33, 11, 23, 153, 78};
    std::vector<int> reordered_copy;

    reordered_copy = re_order(original);

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
}