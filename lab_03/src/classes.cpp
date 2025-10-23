#include <iostream>
#include <cmath>
#include <exception>

#include "classes.h"

std::ostream& operator<<(std::ostream& os, const Figure& figure)
{
    figure.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& figure)
{
    figure.read(is);
    return is;
}

Triangle::Triangle(
    std::pair<double, double> a,
    std::pair<double, double> b,
    std::pair<double, double> c
)
{
    double a_b = sqrt(pow(b.first - a.first, 2) + pow(b.second - a.second, 2));
    double a_c = sqrt(pow(c.first - a.first, 2) + pow(c.second - a.second, 2));
    double b_c = sqrt(pow(c.first - b.first, 2) + pow(c.second - b.second, 2));
    double epsilon = 1e-9;
    if ((a_b + a_c) <= (b_c + epsilon) ||
        (a_c + b_c) <= (a_b + epsilon) ||
        (b_c + a_b) <= (a_c + epsilon))
    {
        throw std::invalid_argument("invalid triangle coords");
    }
    this->a = a;
    this->b = b;
    this->c = c;
}

Triangle::Triangle(
    const Triangle& other
)
{
    this->a = other.a;
    this->b = other.b;
    this->c = other.c;
}

Triangle::Triangle(
    Triangle&& other
) noexcept
{
    this->a = other.a;
    this->b = other.b;
    this->c = other.c;
    other.a = {0, 0};
    other.b = {0, 0};
    other.c = {0, 0};
}

std::pair<double, double> Triangle::find_center() const
{
    std::pair<double, double> center = {(a.first + b.first + c.first) / 3, (a.second + b.second + c.second) / 3};
    return center;
}

Triangle::operator double() const
{
    double square = abs((a.first * (b.second - c.second) + b.first * (c.second - a.second) + c.first * (a.second -
        b.second)) / 2);
    return square;
}

void Triangle::print(std::ostream& os) const
{
    os << "Triangle: (" << a.first << ", " << a.second << "), ("
        << b.first << ", " << b.second << "), ("
        << c.first << ", " << c.second << ")" << std::endl;
}

void Triangle::read(std::istream& is)
{
    is >> a.first >> a.second >> b.first >> b.second >> c.first >> c.second;
    double a_b = sqrt(pow(b.first - a.first, 2) + pow(b.second - a.second, 2));
    double a_c = sqrt(pow(c.first - a.first, 2) + pow(c.second - a.second, 2));
    double b_c = sqrt(pow(c.first - b.first, 2) + pow(c.second - b.second, 2));
    double epsilon = 1e-9;
    if ((a_b + a_c) <= (b_c + epsilon) ||
        (a_c + b_c) <= (a_b + epsilon) ||
        (b_c + a_b) <= (a_c + epsilon))
    {
        throw std::invalid_argument("invalid triangle coords");
    }
}

Triangle& Triangle::operator=(const Triangle& other)
{
    this->a = other.a;
    this->b = other.b;
    this->c = other.c;
    return *this;
}

Triangle& Triangle::operator=(Triangle&& other) noexcept
{
    this->a = other.a;
    this->b = other.b;
    this->c = other.c;
    other.a = {0, 0};
    other.b = {0, 0};
    other.c = {0, 0};
    return *this;
}

bool Triangle::operator==(const Triangle& other) const
{
    return a == other.a && b == other.b && c == other.c;
}

Rectangle::Rectangle(std::pair<double, double> left_point, std::pair<double, double> right_point)
{
    double width = std::abs(right_point.first - left_point.first);
    double height = std::abs(right_point.second - left_point.second);

    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument("invalid rectangle coords: width and height must be positive");
    }
    this->left_point = left_point;
    this->right_point = right_point;
}

Rectangle::Rectangle(const Rectangle& other)
{
    this->left_point = other.left_point;
    this->right_point = other.right_point;
}

Rectangle::Rectangle(Rectangle&& other) noexcept
{
    this->left_point = other.left_point;
    this->right_point = other.right_point;
    other.left_point = {0, 0};
    other.right_point = {0, 0};
}

std::pair<double, double> Rectangle::find_center() const
{
    std::pair<double, double> center = {
        (left_point.first + right_point.first) / 2, (left_point.second + right_point.second) / 2
    };
    return center;
}

Rectangle::operator double() const
{
    double square = abs(right_point.first - left_point.first) * abs(right_point.second - left_point.second);
    return square;
}

void Rectangle::print(std::ostream& os) const
{
    os << "Rectangle: (" << left_point.first << ", " << left_point.second << "), ("
        << right_point.first << ", " << right_point.second << ")" << std::endl;
}

void Rectangle::read(std::istream& is)
{
    is >> left_point.first >> left_point.second >> right_point.first >> right_point.second;
    if (!(abs(left_point.first - right_point.first) * abs(left_point.second - right_point.second) > 0))
    {
        throw std::invalid_argument("invalid rectangle coords");
    }
}

Rectangle& Rectangle::operator=(const Rectangle& other)
{
    this->left_point = other.left_point;
    this->right_point = other.right_point;
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept
{
    this->left_point = other.left_point;
    this->right_point = other.right_point;
    other.left_point = {0, 0};
    other.right_point = {0, 0};
    return *this;
}

bool Rectangle::operator==(const Rectangle& other) const
{
    return this->left_point == other.left_point && this->right_point == other.right_point;
}

Square::Square(std::pair<double, double> left_point, std::pair<double, double> top_right)
    : Rectangle(left_point, top_right)
{
    double width = std::abs(right_point.first - left_point.first);
    double height = std::abs(right_point.second - left_point.second);

    const double epsilon = 1e-9;
    if (std::abs(width - height) > epsilon)
    {
        throw std::invalid_argument("invalid square coords: sides must be equal");
    }
}

Square::Square(const Square& other) : Rectangle(other)
{
}


Square::Square(Square&& other) noexcept : Rectangle(std::move(other))
{
}

void Square::print(std::ostream& os) const
{
    os << "Square: (" << left_point.first << ", " << left_point.second << "), (" << right_point.first << ", " <<
        right_point.second << ")" << std::endl;
}

void Square::read(std::istream& is)
{
    is >> left_point.first >> left_point.second >> right_point.first >> right_point.second;

    double width = std::abs(right_point.first - left_point.first);
    double height = std::abs(right_point.second - left_point.second);
    const double epsilon = 1e-9;

    if (width <= 0 || height <= 0 || std::abs(width - height) > epsilon)
    {
        throw std::invalid_argument("invalid square coords");
    }
}

Square& Square::operator=(const Square& other)
{
    Rectangle::operator=(other);
    return *this;
}

Square& Square::operator=(Square&& other) noexcept
{
    Rectangle::operator=(std::move(other));
    return *this;
}

bool Square::operator==(const Square& other) const
{
    return this->left_point == other.left_point && this->right_point == other.right_point;
}
