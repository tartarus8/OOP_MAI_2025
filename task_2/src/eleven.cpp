#include "eleven.h"
#include <algorithm>
using namespace std;

unsigned char Eleven::charToDigit(char c) {
    if (c >= '0' && c <= '9') return static_cast<unsigned char>(c - '0');
    if (c == 'A' || c == 'a') return 10;
    throw invalid_argument("Invalid base-11 digit");
}

char Eleven::digitToChar(unsigned char d) {
    if (d <= 9) return static_cast<char>('0' + d);
    if (d == 10) return 'A';
    throw invalid_argument("Digit out of range for base-11");
}

Array Eleven::stripLeadingZerosLE(const Array& le) {
    size_t n = le.size();
    while (n > 0 && le.at(n - 1) == 0) --n;
    if (n == 0) return Array();
    unsigned char* tmp = new unsigned char[n];
    for (size_t i = 0; i < n; ++i) tmp[i] = le.at(i);
    Array out = Array::fromRaw(tmp, n);
    delete[] tmp;
    return out;
}

Eleven::Eleven() : digits_() {}

Eleven::Eleven(unsigned long long v) {
    if (v == 0) { digits_ = Array(); return; }
    unsigned char buf[64];
    size_t k = 0;
    while (v > 0) {
        buf[k++] = static_cast<unsigned char>(v % BASE);
        v /= BASE;
    }
    digits_ = Array::fromRaw(buf, k);
    digits_ = stripLeadingZerosLE(digits_);
}

Eleven::Eleven(const string& s) {
    if (s.empty()) throw invalid_argument("Empty string");
    Eleven acc; // 0
    for (char c : s) {
        unsigned char d = charToDigit(c);
        if (acc.digits_.size() == 0) {
        } else {
            Array zero1(1, 0);
            acc = Eleven(Array::concat(zero1, acc.digits_));
        }
        if (d != 0) {
            Eleven addend(static_cast<unsigned long long>(d));
            acc = acc.add(addend);
        }
    }
    digits_ = stripLeadingZerosLE(acc.digits_);
}

string Eleven::toString() const {
    if (digits_.size() == 0) return "0";
    string out;
    out.reserve(digits_.size());
    for (size_t i = digits_.size(); i-- > 0;) {
        out.push_back(digitToChar(digits_.at(i)));
    }
    return out;
}

bool Eleven::isZero() const noexcept {
    return digits_.size() == 0;
}

int Eleven::compare(const Eleven& other) const noexcept {
    size_t na = digits_.size();
    size_t nb = other.digits_.size();
    if (na != nb) return (na < nb) ? -1 : 1;
    for (size_t i = na; i-- > 0;) {
        unsigned char a = digits_.at(i);
        unsigned char b = other.digits_.at(i);
        if (a != b) return (a < b) ? -1 : 1;
    }
    return 0;
}

Array Eleven::addLE(const Array& a, const Array& b) {
    const size_t na = a.size(), nb = b.size();
    const size_t n = std::max(na, nb);
    unique_ptr<unsigned char[]> tmp = make_unique<unsigned char[]>(n + 1);
    unsigned carry = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned av = (i < na) ? a.at(i) : 0;
        unsigned bv = (i < nb) ? b.at(i) : 0;
        unsigned s = av + bv + carry;
        tmp[i] = static_cast<unsigned char>(s % BASE);
        carry = s / BASE;
    }
    size_t outN = n;
    if (carry) { tmp[n] = static_cast<unsigned char>(carry); ++outN; }
    Array out = Array::fromRaw(tmp.get(), outN);
    return stripLeadingZerosLE(out);
}

Array Eleven::subLE(const Array& a, const Array& b) {
    const size_t na = a.size(), nb = b.size();
    if (na < nb) throw invalid_argument("Negative result");
    unique_ptr<unsigned char[]> tmp = std::make_unique<unsigned char[]>(na);
    int borrow = 0;
    for (size_t i = 0; i < na; ++i) {
        int av = a.at(i);
        int bv = (i < nb) ? b.at(i) : 0;
        int diff = av - bv - borrow;
        if (diff < 0) { diff += BASE; borrow = 1; }
        else borrow = 0;
        if (diff < 0 || diff >= static_cast<int>(BASE)) throw logic_error("subLE internal error");
        tmp[i] = static_cast<unsigned char>(diff);
    }
    if (borrow != 0) throw invalid_argument("Negative result");
    Array out = Array::fromRaw(tmp.get(), na);
    return stripLeadingZerosLE(out);
}

Eleven Eleven::add(const Eleven& rhs) const {
    return Eleven(addLE(this->digits_, rhs.digits_));
}

Eleven Eleven::sub(const Eleven& rhs) const {
    if (this->compare(rhs) < 0) throw invalid_argument("Subtraction would be negative");
    return Eleven(subLE(this->digits_, rhs.digits_));
}
