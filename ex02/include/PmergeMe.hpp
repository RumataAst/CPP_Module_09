# ifndef  PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <iostream>
#include <deque>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <limits.h>
#include <ctime>

# define JACOBSTAHL_SIZE 10

class Alg {
private:
    std::vector<int>    vector_seq;
    std::deque<int>     deque_seq;

    std::clock_t        vector_time, deque_time;

    std::string         user_input;
    std::vector<int>    jacobstahl_seq;

public:
    Alg(std::string &number_seq);
    Alg(const Alg &copy);
    Alg &operator=(const Alg &source);
    ~Alg();

    
    void    sorting(std::vector<int> &vector_seq, size_t max_power_of_2, int &number_compare);
    void    merging(std::vector<int> &vector_seq, size_t group_size, int &number_compare);


    void    generate_jacobstahl();
    void    binary_insert_index(std::vector<int>& main_seq, const std::vector<int>& group, int &number_compare, int right_index);
    void    processGroups(const std::vector<int>& vector_seq, std::vector<int>& main_seq, std::vector<int>& pend, size_t group_size);
    std::vector<int> reorderPend(const std::vector<int>& pend, size_t group_size);


    void    pass_to_containers(std::string &number_seq);
    void    print_result() const;

    void    sort_vector_seq();
    void    sort_deque_time();



    
//debugging
    void    print_vector(std::vector<int> vector) {
        for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
};

class NegativeNumber : public std::exception{
public:
    virtual const char *what() const throw() {
        return "Negative number in the string";
    }   
};

class DuplicateNumber : public std::exception{
    public:
        virtual const char *what() const throw() {
            return "Duplicate number in the string";
        }   
    };
    



#endif