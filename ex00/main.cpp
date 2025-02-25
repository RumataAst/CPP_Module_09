#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <map>
#include <string>
#include <cstdlib>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Please add file as argument: ./btc example.txt\n";
        return -1;
    }

    (void)argv;

    std::ifstream                       iFile;
    std::string                         line = "";
    std::map<std::string, double>       data;
    std::string                         date, valueStr;
    double                              value = 0;
      
    try {
        iFile.open("data.csv");
        if (!iFile.is_open()) {
            throw std::runtime_error("File could not be opened.");
        }
    }
    catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::cout << "starting to read from file\n";
    while (getline(iFile, line)) {
        if (line.empty()) {
            continue;
        }
        // working with line directly
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            std::string date = line.substr(0, commaPos);
            std::string valueStr = line.substr(commaPos + 1);
            //check for atof 0 return
            value = std::atof(valueStr.c_str());
            if (value == 0 && valueStr != "0") {
            // Handle invalid value case
                data[date] = -1;  // Store "NoN" if conversion failed
            } else {
                data[date] = value;  // Store valid numeric value
            }
        }
        // // example with working
        // std::stringstream ss(line);
        // if (std::getline(ss, date, ',') && std::getline(ss, valueStr)) {
        //     std::stringstream valueStream(valueStr);
        //     double value = 0.0;
        //     valueStream >> value;

        //     data[date] = value;
        // }
    }

    iFile.close();
    //print map
    for (std::map<std::string, double>::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::cout << "Date: " << it->first << ", Value: " << it->second << std::endl;
    }

    return 0;
}