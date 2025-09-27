#include "classes.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>


Seven::Seven() = default;

Seven::Seven(const size_t& n, unsigned char* t)
{
    size = n;
    if (size <= 0) throw std::invalid_argument("size must be > 0");
    if (t == nullptr) throw std::invalid_argument("array pointer cannot be null");
    digits = size > 0 ? new unsigned char[size] : nullptr;
    for (size_t i = 0; i < size; i++)
    {
        if (t[i] > 6)
        {
            delete[] digits;
            throw std::out_of_range("digit out of range (0..6)");
        }
        digits[i] = t[i];
    }
}

Seven::Seven(const std::initializer_list<unsigned char>& t)
{
    size = t.size();
    if (size == 0) throw std::invalid_argument("initializer_list cannot be empty");
    size_t i = 0;
    digits = new unsigned char[size];
    for (const auto& x : t)
    {
        if (x > 6)
        {
            delete[] digits;
            throw std::out_of_range("digit out of range (0..6)");
        }
        digits[i] = x;
        i++;
    }
}

Seven::Seven(const std::string& t)
{
    size = t.length();
    if (size == 0) throw std::invalid_argument("string cannot be empty");
    digits = new unsigned char[size];
    for (size_t i = 0; i < size; i++)
    {
        char c = t[i];
        if (c < '0' || c > '6')
        {
            delete[] digits;
            throw std::out_of_range("invalid digit in string");
        }
        digits[size - i - 1] = t[i] - '0';
    }
}


Seven::Seven(const Seven& other)
{
    size = other.size;
    digits = size > 0 ? new unsigned char[size] : nullptr;
    for (size_t i = 0; i < size; i++)
    {
        digits[i] = other.digits[i];
    }
}

Seven::Seven(Seven&& other) noexcept
{
    size = other.size;
    digits = other.digits;
    other.digits = nullptr;
    other.size = 0;
}

Seven::~Seven() noexcept
{
    delete[] digits;
}

Seven Seven::add(const Seven& other) const
{
    size_t max_size = std::max(size, other.size);
    unsigned char* result_digits = new unsigned char[max_size + 1]();

    unsigned char carry = 0;
    size_t result_size = 0;

    for (size_t i = 0; i < max_size || carry > 0; i++)
    {
        unsigned char digit1 = i < size ? digits[i] : 0;
        unsigned char digit2 = i < other.size ? other.digits[i] : 0;

        unsigned char sum = static_cast<unsigned char>(digit1 + digit2 + carry);
        result_digits[i] = static_cast<unsigned char>(sum % 7);
        carry = static_cast<unsigned char>(sum / 7);
        result_size = i + 1;
    }

    Seven result(result_size, result_digits);
    delete[] result_digits;

    return result;
}

Seven Seven::subtract(const Seven& other) const
{
    if (is_less(other))
    {
        return Seven();
    }

    unsigned char* result_digits = new unsigned char[size]();
    unsigned char borrow = 0;

    for (size_t i = 0; i < size; i++)
    {
        unsigned char digit1 = digits[i];
        unsigned char digit2 = (i < other.size) ? other.digits[i] : 0;

        int diff = static_cast<int>(digit1) - static_cast<int>(digit2) - static_cast<int>(borrow);

        if (diff < 0)
        {
            diff += 7;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result_digits[i] = static_cast<unsigned char>(diff);
    }

    size_t result_size = size;
    while (result_size > 1 && result_digits[result_size - 1] == 0)
    {
        result_size--;
    }

    Seven result(result_size, result_digits);
    delete[] result_digits;

    return result;
}

bool Seven::is_equal(const Seven& other) const
{
    if (size != other.size) return false;
    for (size_t i = 0; i < size; i++)
    {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Seven::is_greater(const Seven& other) const
{
    if (size > other.size) return true;
    if (size < other.size) return false;
    for (size_t i = size; i-- > 0;)
    {
        if (digits[i] > other.digits[i]) return true;
        if (digits[i] < other.digits[i]) return false;
    }
    return false;
}

bool Seven::is_less(const Seven& other) const
{
    if (size < other.size) return true;
    if (size > other.size) return false;
    for (size_t i = size; i-- > 0;)
    {
        if (digits[i] < other.digits[i]) return true;
        if (digits[i] > other.digits[i]) return false;
    }
    return false;
}

std::string Seven::to_string() const
{
    if (size == 0) return "0";
    std::string res;
    res.reserve(size);
    for (size_t i = size; i-- > 0;)
    {
        res.push_back(static_cast<char>('0' + digits[i]));
    }
    return res;
}

size_t Seven::get_size() const
{
    return size;
}
