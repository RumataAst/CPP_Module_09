#include <iostream>
#include <vector>
#include <algorithm>


int get_index(std::vector<int> &original_vector, std::vector<int> &where_to_insert, int number) {
    int index = 0;
    int target_value = number;
    std::vector<int>::iterator it_original = std::find(original_vector.begin(), original_vector.end(), number);
    if (std::next(it_original) != original_vector.end()) {
        it_original++;
        std::vector<int>::iterator it_insert = std::find(where_to_insert.begin(), where_to_insert.end(), *it_original);
        index = static_cast<int>(it_insert - where_to_insert.begin());
    }
    else {
        index = where_to_insert.size();
    }

    return index;
}

int main (void) {
    std::vector<int> original_vector;

    for (int it = 0; it < 6; ++it) {
        original_vector.push_back(it+2);
    }

    for (auto it = original_vector.begin(); it != original_vector.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;



    std::vector<int> where_to_insert;
    where_to_insert.push_back(3);
    where_to_insert.push_back(5);
    where_to_insert.push_back(6);


    for (auto it = where_to_insert.begin(); it != where_to_insert.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    int     first_number = 2, second_group = 4, third_group = 7;

    std::cout << "Value is " << first_number << std::endl;
    int index = get_index(original_vector, where_to_insert, first_number);

    std::cout << "Index is " << index << std::endl;
    std::cout << "PUSHING THE VALUE \n";
    where_to_insert.insert(where_to_insert.begin() + index, first_number);

    std::cout << "Value is " << second_group << std::endl;
    index = get_index(original_vector, where_to_insert, second_group);
    where_to_insert.insert(where_to_insert.begin() + index, second_group);

    std::cout << "Index is " << index << std::endl;


    std::cout << "Value is " << third_group << std::endl;
    index = get_index(original_vector, where_to_insert, third_group);
    where_to_insert.insert(where_to_insert.begin() + index, third_group);

    std::cout << "Index is " << index << std::endl;



    for (auto it = where_to_insert.begin(); it != where_to_insert.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
