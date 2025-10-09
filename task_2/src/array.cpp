#include "array.h"
#include <utility>
using namespace std;
Array::Array() : n_{0}, buf_{nullptr} {}

Array::Array(const size_t& n, unsigned char t) : n_{n}, buf_{nullptr} {
    if (n_ > 0) {
        buf_ = make_unique<unsigned char[]>(n_);
        for (size_t i = 0; i < n_; ++i) buf_[i] = t;
    }
}

Array::Array(const initializer_list<unsigned char>& t) : Array(t.size()) {
    size_t i = 0;
    for (auto v : t) {
        if (v > 255) throw invalid_argument("byte out of range");
        buf_[i++] = v;
    }
}

Array::Array(const string& bytes) : Array(bytes.size()) {
    for (size_t i = 0; i < n_; ++i) buf_[i] = static_cast<unsigned char>(bytes[i]);
}

Array::Array(const Array& other) : Array(other.n_) {
    for (size_t i = 0; i < n_; ++i) buf_[i] = other.buf_[i];
}

Array::Array(Array&& other) noexcept : n_{other.n_}, buf_{std::move(other.buf_)} {
    other.n_ = 0;
}

Array::~Array() noexcept = default;

size_t Array::size() const noexcept { return n_; }

unsigned char Array::at(size_t i) const {
    if (i >= n_) throw out_of_range("Array::at");
    return buf_ ? buf_[i] : 0;
}

const unsigned char* Array::data() const noexcept { return buf_.get(); }

Array Array::fromRaw(const unsigned char* src, size_t n) {
    Array a(n);
    for (size_t i = 0; i < n; ++i) a.buf_[i] = src[i];
    return a;
}

Array Array::concat(const Array& a, const Array& b) {
    Array out(a.n_ + b.n_);
    for (size_t i = 0; i < a.n_; ++i) out.buf_[i] = a.buf_[i];
    for (size_t j = 0; j < b.n_; ++j) out.buf_[a.n_ + j] = b.buf_[j];
    return out;
}

Array& Array::operator=(const Array& other) {
    if (this == &other) return *this;
    n_ = other.n_;
    if (n_ == 0) {
        buf_.reset();
        return *this;
    }
    auto tmp = make_unique<unsigned char[]>(n_);
    for (size_t i = 0; i < n_; ++i) tmp[i] = other.buf_[i];
    buf_ = std::move(tmp);
    return *this;
}

Array& Array::operator=(Array&& other) noexcept {
    if (this == &other) return *this;
    n_ = other.n_;
    buf_ = std::move(other.buf_);
    other.n_ = 0;
    return *this;
}

