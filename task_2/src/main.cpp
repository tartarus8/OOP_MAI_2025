#include "eleven.h"
#include <iostream>

int main() {
    Eleven a("A9");     // base-11: A(10)*11 + 9 = 119
    Eleven b(25);       // из десятичного ULL (конструктор сам переводит)

    auto c = a.add(b);  // c = a + b
    auto d = c.sub(a);  // d = c - a  == b

    std::cout << "a = " << a.toString() << "\n";
    std::cout << "b = " << b.toString() << "\n";
    std::cout << "c = " << c.toString() << "\n";
    std::cout << "d = " << d.toString() << "\n";

    std::cout << std::boolalpha
              << "a > b? " << a.greaterThan(b) << "\n"
              << "a < b? " << a.lessThan(b) << "\n"
              << "b == d? " << b.equals(d) << "\n";
}
