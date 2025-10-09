#pragma once
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <string>
#include <stdexcept>
using namespace std;

class Array {
public:
    Array();
    Array(const size_t& n, unsigned char t = 0);
    Array(const std::initializer_list<unsigned char>& t);
    Array(const std::string& bytes);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    virtual ~Array() noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    size_t size() const noexcept;
    unsigned char at(size_t i) const;
    const unsigned char* data() const noexcept;

    static Array fromRaw(const unsigned char* src, size_t n);
    static Array concat(const Array& a, const Array& b);

private:
    size_t n_{0};
    std::unique_ptr<unsigned char[]> buf_;
};

