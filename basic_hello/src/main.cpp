#include <iostream>

#include "speech.h"

int main(int, char **)
{
    std::cout << "Hello, from basic_hello!\n";
    std::cout << get_phrase() << std::endl;

    double a{1.5}, b{}, c{};
    double result{a / b};
    std::cout << a << "/" << b << " = " << result << std::endl;
    std::cout << result << " + " << a << " = " << result + a << std::endl;
    result = b / c;
    std::cout << b << "/" << c << " = " << result << std::endl;
}
