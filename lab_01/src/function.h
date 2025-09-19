#pragma once
#include <exception>
#include <string>

class Exception : public std::exception
{
private:
    std::string message;

public:
    Exception(std::string message) noexcept : message(message) { }

    const char* what() const noexcept override { return message.c_str(); }
};

class InvalidInput : public Exception
{
public:
    InvalidInput(std::string message) : Exception(message) { }
};


class Solution
{
private:
    int couting_units(int n);

public:
    int calculate_sum_range(int start, int end);
};
