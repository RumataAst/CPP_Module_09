#include "BitcoinExchange.hpp"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Please add file as argument: ./btc example.txt\n";
        return -1;
    }
    std::string     iFileStr = argv[1];
    std::ifstream   iFile(iFileStr.c_str());
    BitcoinExchange initial_data;


    if (!iFile.is_open()) {
        std::cerr << "File " << iFileStr << " coulnd't be open\n";
        return -1;
    }
    initial_data.showMerge(iFile);
    
    // catch(std::exception &e) {
    //     std::cerr << e.what() << std::endl;
    // } 
    iFile.close();

    // std::cout << initial_data;
    return 0;
}