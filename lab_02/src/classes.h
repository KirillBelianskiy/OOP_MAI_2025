#pragma once
#include <string>

class Seven
{
private:
    unsigned char* digits{nullptr};
    size_t size{0};

public:
    Seven();
    Seven(const size_t& n, unsigned char* t);
    Seven(const std::initializer_list<unsigned char>& t);
    Seven(const std::string& t);

    Seven(const Seven& other);
    Seven(Seven&& other) noexcept;
    virtual ~Seven() noexcept;

    Seven& operator=(const Seven& other) = delete;
    Seven& operator=(Seven&& other) noexcept = delete;

    Seven add(const Seven& other) const;
    Seven subtract(const Seven& other) const;
    bool is_equal(const Seven& other) const;
    bool is_greater(const Seven& other) const;
    bool is_less(const Seven& other) const;

    std::string to_string() const;
    size_t get_size() const;
};
