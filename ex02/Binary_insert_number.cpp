#include <iostream>
#include <cmath>

int F(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

int    main(int argc, char *argv[]) {
    if (argc != 2)
        return 1;

    std::string number_string = argv[1];
    int number = std::stod(number_string);

    std::cout << F(number);
    return 0;
}