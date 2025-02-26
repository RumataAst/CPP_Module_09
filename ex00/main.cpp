#include "BitcoinExchange.hpp"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Please add file as argument: ./btc example.txt\n";
        return -1;
    }
    
    BitcoinExchange initial_data;
    (void)argv;
    std::cout << initial_data;
    return 0;
}