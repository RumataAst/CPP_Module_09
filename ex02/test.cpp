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

    size_t jacob_seq_index = 0;
    for (size_t original_index = 0; original_index < original.size(); ++original_index) {
        if (original_index < jacob_seq[jacob_seq_index]) {
            
        }
    }
}

int main(void) {
    std::vector<int> original = {15, 5, 2, 33, 11, 23};
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