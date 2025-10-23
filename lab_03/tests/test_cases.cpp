#include <gtest/gtest.h>
#include <sstream>

#include "../src/classes.h"

using P = std::pair<double, double>;

TEST(TriangleTests, ConstructorValid)
{
    ASSERT_NO_THROW(Triangle t(P{0, 0}, P{4, 0}, P{0, 3}));
}

TEST(TriangleTests, ConstructorInvalid)
{
    ASSERT_THROW(Triangle t(P{0, 0}, P{1, 1}, P{2, 2}), std::invalid_argument);
}

TEST(TriangleTests, FindCenter)
{
    Triangle t(P{0, 0}, P{3, 0}, P{0, 3});
    P center = t.find_center();
    ASSERT_EQ(center.first, 1.0);
    ASSERT_EQ(center.second, 1.0);
}

TEST(TriangleTests, Area)
{
    Triangle t(P{0, 0}, P{4, 0}, P{0, 3});
    double area = static_cast<double>(t);
    ASSERT_DOUBLE_EQ(area, 6.0);
}

TEST(TriangleTests, Equality)
{
    Triangle t1(P{0, 0}, P{4, 0}, P{0, 3});
    Triangle t2(P{0, 0}, P{4, 0}, P{0, 3});
    Triangle t3(P{1, 1}, P{2, 2}, P{3, 1});

    ASSERT_TRUE(t1 == t2);
    ASSERT_FALSE(t1 == t3);
}

TEST(TriangleTests, Copy)
{
    Triangle t1(P{0, 0}, P{4, 0}, P{0, 3});

    Triangle t2 = t1;
    ASSERT_TRUE(t1 == t2);

    Triangle t3(P{1, 1}, P{2, 2}, P{3, 1});
    ASSERT_FALSE(t1 == t3);
    t3 = t1;
    ASSERT_TRUE(t1 == t3);
}

TEST(TriangleTests, Move)
{
    Triangle t1(P{0, 0}, P{4, 0}, P{0, 3});
    Triangle t1_copy = t1;

    Triangle t2 = std::move(t1);
    ASSERT_TRUE(t2 == t1_copy);

    Triangle t3(P{1, 1}, P{2, 2}, P{3, 1});
    t3 = std::move(t2);
    ASSERT_TRUE(t3 == t1_copy);
}

TEST(TriangleTests, ReadValid)
{
    std::stringstream ss("0 0 4 0 0 3");
    Triangle t(P{1, 1}, P{2, 2}, P{3, 1});
    ss >> t;
    ASSERT_DOUBLE_EQ(static_cast<double>(t), 6.0);
}

TEST(TriangleTests, ReadInvalid)
{
    std::stringstream ss("0 0 1 1 2 2");
    Triangle t(P{0, 0}, P{4, 0}, P{0, 3});
    ASSERT_THROW(ss >> t, std::invalid_argument);
}

TEST(TriangleTests, Print)
{
    Triangle t(P{0, 0}, P{4, 0}, P{0, 3});
    std::stringstream ss;
    ss << t;
    ASSERT_EQ(ss.str(), "Triangle: (0, 0), (4, 0), (0, 3)\n");
}


TEST(RectangleTests, ConstructorValid)
{
    ASSERT_NO_THROW(Rectangle r(P{0, 0}, P{5, 2}));
}

TEST(RectangleTests, ConstructorInvalid)
{
    ASSERT_THROW(Rectangle r(P{0, 0}, P{0, 5}), std::invalid_argument);
    ASSERT_THROW(Rectangle r(P{0, 0}, P{5, 0}), std::invalid_argument);
}

TEST(RectangleTests, FindCenter)
{
    Rectangle r(P{1, 1}, P{5, 3});
    P center = r.find_center();
    ASSERT_EQ(center.first, 3.0);
    ASSERT_EQ(center.second, 2.0);
}

TEST(RectangleTests, Area)
{
    Rectangle r(P{1, 1}, P{6, 4});
    double area = static_cast<double>(r);
    ASSERT_DOUBLE_EQ(area, 15.0);
}

TEST(RectangleTests, ReadValid)
{
    std::stringstream ss("1 1 6 4");
    Rectangle r(P{0, 0}, P{1, 1});
    ss >> r;
    ASSERT_DOUBLE_EQ(static_cast<double>(r), 15.0);
}

TEST(RectangleTests, ReadInvalid)
{
    std::stringstream ss("1 1 1 5");
    Rectangle r(P{0, 0}, P{2, 2});
    ASSERT_THROW(ss >> r, std::invalid_argument);
}

TEST(SquareTests, ConstructorValid)
{
    ASSERT_NO_THROW(Square s(P{0, 0}, P{5, 5}));
}

TEST(SquareTests, ConstructorInvalidNotSquare)
{
    ASSERT_THROW(Square s(P{0, 0}, P{5, 4}), std::invalid_argument);
}

TEST(SquareTests, ConstructorInvalidDegenerate)
{
    ASSERT_THROW(Square s(P{0, 0}, P{0, 0}), std::invalid_argument);
}

TEST(SquareTests, AreaAndCenter)
{
    Square s(P{0, 0}, P{4, 4});

    P center = s.find_center();
    ASSERT_EQ(center.first, 2.0);
    ASSERT_EQ(center.second, 2.0);

    double area = static_cast<double>(s);
    ASSERT_DOUBLE_EQ(area, 16.0);
}

TEST(SquareTests, ReadValid)
{
    std::stringstream ss("0 0 4 4");
    Square s(P{0, 0}, P{1, 1});
    ss >> s;
    ASSERT_DOUBLE_EQ(static_cast<double>(s), 16.0);
}

TEST(SquareTests, ReadInvalidNotSquare)
{
    std::stringstream ss("0 0 4 3");
    Square s(P{0, 0}, P{1, 1});
    ASSERT_THROW(ss >> s, std::invalid_argument);
}

TEST(SquareTests, Polymorphism)
{
    std::unique_ptr<Figure> fig = std::make_unique<Square>(P{0, 0}, P{2, 2});

    P center = fig->find_center();
    ASSERT_EQ(center.first, 1.0);
    ASSERT_EQ(center.second, 1.0);

    double area = static_cast<double>(*fig);
    ASSERT_DOUBLE_EQ(area, 4.0);

    std::stringstream ss;
    ss << *fig;
    ASSERT_EQ(ss.str(), "Square: (0, 0), (2, 2)\n");
}
