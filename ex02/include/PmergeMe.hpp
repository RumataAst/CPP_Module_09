# ifndef  PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <iostream>
#include <deque>
#include <vector>
#include <sstream>
#include <algorithm>

class Alg {
private:
    std::vector<int>    vector_seq;
    std::deque<int>     deque_seq;

    int                 vector_time;
    int                 deque_time;

    std::string         user_input;
public:
    Alg(std::string &number_seq);
    Alg(const Alg &copy);
    Alg &operator=(const Alg &source);
    ~Alg();

    void    pass_to_containers(std::string &number_seq);
    void    print_result() const;

    void    sort_vector_seq();
    void    sort_deque_time();

//debugging
    void    print_vector(std::vector<int> vector) {
        std::cout << "DEBUGGING\n";
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



#endif