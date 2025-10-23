#pragma once
#include <iosfwd>
#include <utility>

class Figure
{
public:
    virtual std::pair<double, double> find_center() const = 0;
    virtual operator double() const = 0;

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;


    virtual ~Figure() = default;
};

std::ostream& operator<<(std::ostream& os, const Figure& figure);
std::istream& operator>>(std::istream& is, Figure& figure);

class Triangle : public Figure
{
private:
    std::pair<double, double> a, b, c;

public:
    Triangle(std::pair<double, double> a, std::pair<double, double> b, std::pair<double, double> c);
    Triangle(const Triangle& other);
    Triangle(Triangle&& other) noexcept;
    ~Triangle() = default;

    std::pair<double, double> find_center() const override;
    operator double() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Triangle& operator=(const Triangle& other);
    Triangle& operator=(Triangle&& other) noexcept;
    bool operator==(const Triangle& other) const;
};


class Rectangle : public Figure
{
protected:
    std::pair<double, double> left_point, right_point;

public:
    Rectangle(std::pair<double, double> left_point, std::pair<double, double> right_point);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;
    ~Rectangle() = default;

    std::pair<double, double> find_center() const override;
    operator double() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;
    bool operator==(const Rectangle& other) const;
};

class Square : public Rectangle
{
public:
    Square(std::pair<double, double> left_point, std::pair<double, double> right_point);
    Square(const Square& other);
    Square(Square&& other) noexcept;
    ~Square() = default;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Square& operator=(const Square& other);
    Square& operator=(Square&& other) noexcept;
    bool operator==(const Square& other) const;
};
