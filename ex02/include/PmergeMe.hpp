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

class MergeSorter  {
private:
    std::vector<int>    vector_seq;
    std::deque<int>     deque_seq;

    std::clock_t        vector_time, deque_time;

    std::string         user_input;
    std::vector<int>    jacobstahl_seq;

public:
    MergeSorter(std::string &number_seq);
    MergeSorter(const MergeSorter &copy);
    MergeSorter &operator=(const MergeSorter &source);
    ~MergeSorter();

    template <typename Container>
    void    sorting(Container &Container_seq, size_t max_power_of_2, int &number_compare);
    template <typename Container>
    void    merging(Container &Container_seq, size_t group_size, int &number_compare);


    template <typename Container>
    void    binary_insert_index(Container& main_seq, const Container& group, int &number_compare, int right_index);
    template <typename Container>
    void    processGroups(const Container& Container_seq, Container& main_seq, Container& pend, size_t group_size);
    template <typename Container>
    Container reorderPend(const Container& pend, size_t group_size);
    
    
    void    pass_to_containers(std::string &number_seq);
    void    generate_jacobstahl();
    void    print_result() const;

    void    sort_container_seq(std::string type_container);



    
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
    
class NotANumber : public std::exception{
    public:
        virtual const char *what() const throw() {
            return "Please use only unique positive numbers";
        }   
    };

#include "PmergeMe.tpp"


#endif