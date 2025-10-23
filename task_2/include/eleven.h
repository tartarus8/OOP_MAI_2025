#ifndef ELEVEN_H
#define ELEVEN_H

#include <cstddef>
#include <initializer_list>
#include <string>
#include <stdexcept>

class Eleven {
public:
    Eleven(); // no-argument initializer
    Eleven(size_t n, unsigned char t = 0); // length-argument initializer
    Eleven(const std::initializer_list<unsigned char>& t); // list initializer
    Eleven(const std::string& t); // list-to-eleven initializer
    Eleven(const Eleven& other); // initializer by copy
    Eleven(Eleven&& other) noexcept; // initializer by reallocating
    ~Eleven() noexcept; // destructor

    // arithmetics
    Eleven add(const Eleven& rhs) const;
    Eleven subtract(const Eleven& rhs) const;

    // comparisons
    bool isEqual(const Eleven& rhs) const;
    bool isLess(const Eleven& rhs) const;
    bool isGreater(const Eleven& rhs) const;

    std::string toString() const;

private:
    unsigned char* data_;   // dynamic digit array (0-10)
    size_t length_;         // number of digits

    void trim(); // leading zeroes deleter
};

#endif
