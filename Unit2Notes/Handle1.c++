// -----------
// Handle1.c++
// -----------

#include "gtest/gtest.h"

#include "Shapes.h"
#include "Handle1.h"

using namespace std;

struct Shape : Handle<AbstractShape> {
    Shape (AbstractShape* p) :
            Handle<AbstractShape> (p)
        {}

    Shape             (const Shape&) = default;
    ~Shape            ()             = default;
    Shape& operator = (const Shape&) = default;

    double area () const {
        return get()->area();}

    void move (int x, int y) {
        return get()->move(x, y);}};

TEST(Handle_Fixture, test_1) {
    const Shape x = new Circle(2, 3, 4);
//  x.move(5, 6);                        // doesn't compile
    ASSERT_EQ(3.14 * 4 * 4, x.area());
//  x.radius();                          // doesn't compile
    }

TEST(Handle_Fixture, test_2) {
    Shape x = new Circle(2, 3, 4);
    x.move(5, 6);
    ASSERT_EQ(new Circle(5, 6, 4), x);
    ASSERT_EQ(3.14 * 4 * 4, x.area());
//  x.radius();                        // doesn't compile
    }

TEST(Handle_Fixture, test_3) {
    const Shape x = new Circle(2, 3, 4);
          Shape y = x;
    ASSERT_EQ(x, y);
    y.move(5, 6);
    ASSERT_EQ(new Circle(2, 3, 4), x);
    ASSERT_EQ(new Circle(5, 6, 4), y);
    ASSERT_EQ(3.14 * 4 * 4, y.area());}

TEST(Handle_Fixture, test_4) {
    const Shape x = new Circle(2, 3, 4);
          Shape y = new Circle(2, 3, 5);
    ASSERT_NE(x, y);
    y = x;
    ASSERT_EQ(x, y);}
