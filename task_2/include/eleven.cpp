#include "eleven.h"
#include <algorithm>

void Eleven::trim() {
    while (length_ > 1 && data_[length_ - 1] == 0) {
        --length_;
    }

    if (length_ == 0) {
        length_ = 1;
        data_[0] = 0;
    }
}

Eleven::Eleven()
    : data_(nullptr), length_(0)
{
    // default value is one-digit zero
    length_ = 1;
    data_ = new unsigned char[1];
    data_[0] = 0;
}

Eleven::Eleven(size_t n, unsigned char t)
    : data_(nullptr), length_(0)
{
    if (t > 10) {
        throw std::invalid_argument("Eleven: invalid digit for base-11");
    }
    length_ = (n == 0 ? 1 : n);
    data_ = new unsigned char[length_];
    for (size_t i = 0; i < length_; ++i) {
        data_[i] = t;
    }

    trim();
}

Eleven::Eleven(const std::initializer_list<unsigned char>& t)
    : data_(nullptr), length_(0)
{
    size_t n = t.size();
    if (n == 0) {
        length_ = 1;
        data_ = new unsigned char[1];
        data_[0] = 0;
        return;
    }
    length_ = n;
    data_ = new unsigned char[length_];
    size_t i = 0;
    for (unsigned char d : t) {
        if (d > 10) {
            throw std::invalid_argument("Eleven: digit out of range (must be 0-10)");
        }
        data_[i++] = d;
    }

    trim();
}

Eleven::Eleven(const std::string& t)
    : data_(nullptr), length_(0)
{
    if (t.empty()) {
        throw std::invalid_argument("Eleven: empty string");
    }
    length_ = t.size();
    data_ = new unsigned char[length_];

    size_t j = 0;
    for (auto i = t.rbegin(); i != t.rend(); ++i) {
        char ch = *i;
        unsigned char digit;
        if (ch >= '0' && ch <= '9') {
            digit = static_cast<unsigned char>(ch - '0');
        } else if (ch == 'A' || ch == 'a') {
            digit = 10;
        } else {
            delete [] data_; // cleaning up alredy allocated memory
            throw std::invalid_argument("Eleven: invalid character in string");
        }
        data_[j++] = digit;
    }

    trim();
}

Eleven::Eleven(const Eleven& other)
    : data_(nullptr), length_(0)
{
    length_ = other.length_;
    data_ = new unsigned char[length_];
    for (size_t i = 0; i < length_; ++i) {
        data_[i] = other.data_[i];
    }
}

Eleven::Eleven(Eleven&& other) noexcept
    : data_(nullptr), length_(0)
{
    data_  = other.data_;
    length_ = other.length_;
    other.data_ = nullptr;
    other.length_ = 0;
}

Eleven::~Eleven() noexcept {
    delete [] data_;
    data_ = nullptr;
    length_ = 0;
}

Eleven Eleven::add(const Eleven& rhs) const {
    size_t maxLen = std::max(length_, rhs.length_);
    Eleven result;
    delete [] result.data_;
    result.length_ = maxLen;
    result.data_ = new unsigned char[maxLen + 1];

    unsigned carry = 0;
    for (size_t i = 0; i < maxLen; ++i) {
        unsigned val1 = (i < length_ ? data_[i] : 0);
        unsigned val2 = (i < rhs.length_ ? rhs.data_[i] : 0);
        unsigned sum  = val1 + val2 + carry;
        result.data_[i] = static_cast<unsigned char>(sum % 11);
        carry = sum / 11;
    }
    if (carry != 0) {
        result.data_[maxLen] = static_cast<unsigned char>(carry);
        result.length_ = maxLen + 1;
    } else {
        result.length_ = maxLen;
    }

    result.trim();
    return result;
}

Eleven Eleven::subtract(const Eleven& rhs) const {
    if (isLess(rhs)) {
        throw std::underflow_error("Eleven: negative result in subtraction");
    }

    Eleven result;
    delete [] result.data_;
    result.length_ = length_;
    result.data_ = new unsigned char[length_];
    unsigned borrow = 0;
    for (size_t i = 0; i < length_; ++i) {
        int val1 = data_[i];
        int val2 = (i < rhs.length_ ? rhs.data_[i] : 0);
        int diff = val1 - val2 - borrow;
        if (diff < 0) {
            diff += 11;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.data_[i] = static_cast<unsigned char>(diff);
    }

    result.trim();
    return result;
}

bool Eleven::isEqual(const Eleven& rhs) const {
    if (length_ != rhs.length_) {
        return false;
    }
    for (size_t i = 0; i < length_; ++i) {
        if (data_[i] != rhs.data_[i]) {
            return false;
        }
    }
    return true;
}

bool Eleven::isLess(const Eleven& rhs) const {
    if (length_ < rhs.length_) {
        return true;
    }
    if (length_ > rhs.length_) {
        return false;
    }

    for (size_t i = length_; i-- > 0; ) {
        if (data_[i] < rhs.data_[i]) {
            return true;
        }
        if (data_[i] > rhs.data_[i]) {
            return false;
        }
    }

    return false;
}

bool Eleven::isGreater(const Eleven& rhs) const {
    return rhs.isLess(*this);
}


std::string Eleven::toString() const {
    if (data_ == nullptr || length_ == 0) {
        return "0";
    }

    std::string out;
    out.reserve(length_);

    for (size_t i = length_; i-- > 0; ) {
        unsigned char d = data_[i];
        char ch = (d < 10) ? static_cast<char>('0' + d) : 'A';
        out.push_back(ch);
    }

    return out;
}