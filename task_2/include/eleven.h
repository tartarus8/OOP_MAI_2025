#pragma once
#include "array.h"
#include <string>
#include <stdexcept>
using namespace std;

class Eleven {
public:
    Eleven();
    explicit Eleven(unsigned long long v);
    explicit Eleven(const string& s);

    Eleven(const Eleven&) = default;
    Eleven(Eleven&&) noexcept = default;
    ~Eleven() = default;

    Eleven& operator=(const Eleven&) = default;
    Eleven& operator=(Eleven&&) noexcept = default;

    string toString() const;
    bool isZero() const noexcept;

    int compare(const Eleven& other) const noexcept;
    bool equals(const Eleven& other) const noexcept { return compare(other) == 0; }
    bool lessThan(const Eleven& other) const noexcept { return compare(other) < 0; }
    bool greaterThan(const Eleven& other) const noexcept { return compare(other) > 0; }

    Eleven add(const Eleven& rhs) const;
    Eleven sub(const Eleven& rhs) const;

    Eleven addAssign(const Eleven& rhs) const { return add(rhs); }
    Eleven subAssign(const Eleven& rhs) const { return sub(rhs); }

    Eleven copy() const { return Eleven(*this); }

private:
    static constexpr unsigned BASE = 11;
    Array digits_;

    static unsigned char charToDigit(char c);
    static char digitToChar(unsigned char d);
    static Array stripLeadingZerosLE(const Array& le);
    static Array addLE(const Array& a, const Array& b);
    static Array subLE(const Array& a, const Array& b);

    explicit Eleven(const Array& leDigits) : digits_(stripLeadingZerosLE(leDigits)) {}
};

