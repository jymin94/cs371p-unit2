// -----------
// Shapes2.c++
// -----------

#include <cassert>  // assert
#include <iostream> // cout, endl, istream, ostream
#include <utility>  // !=

#include "gtest/gtest.h"

using namespace std;
using rel_ops::operator!=;

class Shape {
    friend bool operator == (const Shape& lhs, const Shape& rhs) {
        return lhs.equals(rhs);}

    friend std::istream& operator >> (std::istream& lhs, Shape& rhs) {
        return rhs.read(lhs);}

    friend std::ostream& operator << (std::ostream& lhs, const Shape& rhs) {
        return rhs.write(lhs);}

    private:
        int _x;
        int _y;

    protected:
		/*
		 * has to be the EXACT same signature
		 * but the argument now has to be const Shape& rhs
		 * we have to make sure it's also a circle
		 */
        virtual bool equals (const Shape& rhs) const {
            return (_x == rhs._x) && (_y == rhs._y);}

        virtual std::istream& read (std::istream& in) {
            return in >> _x >> _y;}

        virtual std::ostream& write (std::ostream& out) const {
            return out << _x << " " << _y;}

    public:
        Shape (int x, int y) :
                _x (x),
                _y (y)
            {}

        Shape (const Shape&)  = default;
        Shape (      Shape&&) = default;

        virtual ~Shape ()
            {}

        Shape& operator = (const Shape&)  = default;
        Shape& operator = (      Shape&&) = default;

        virtual double area () const {
            return 0;}

        void move (int x, int y) {
            _x = x;
            _y = y;}};

#include "Shapes2.h"

TEST(Shape_Fixture, test_1) {
    Shape x(2, 3);
    x.move(4, 5);
    ASSERT_EQ(0, x.area());
//  x.radius();               // doesn't compile
    }

TEST(Shape_Fixture, test_2) {
    const Shape x(2, 3);
          Shape y(4, 5);
    ASSERT_NE(x, y);
    y = x;
    ASSERT_EQ(x, y);}

TEST(Shape_Fixture, test_3) {
    Circle x(2, 3, 4);
    x.move(5, 6);
    ASSERT_EQ(3.14 * 4 * 4, x.area());
    ASSERT_EQ(4, x.radius());}

TEST(Shape_Fixture, test_4) {
    const Circle x(2, 3, 4);
          Circle y(2, 3, 5);
    ASSERT_NE(x, y);
    y = x;
    ASSERT_EQ(x, y);}

TEST(Shape_Fixture, test_5) {
//  Circle* const p = new Shape(2, 3);              // doesn't compile
    Shape*  const p = new Circle(2, 3, 4);
    p->move(5, 6);
    ASSERT_EQ(3.14 * 4 * 4, p->area());
//  p->radius();                                    // doesn't compile
    if (Circle* const q = dynamic_cast<Circle*>(p))
        ASSERT_EQ(4, q->radius());
    try {
        Circle& r = dynamic_cast<Circle&>(*p);
        ASSERT_EQ(4, r.radius());}
    catch (const bad_cast& e) {
        ASSERT_TRUE(false);}
    delete p;}

TEST(Shape_Fixture, test_6) {
    const Shape* const p = new Circle(2, 3, 4);
          Shape* const q = new Circle(2, 3, 5);
    ASSERT_NE(*p, *q);
	/* now this works due to overriding the equals operator in Shapes2.h */
//  *q = *p;                                                    // illdefined
	/* invokes Shape's assignment operator
	 * COPIES the x, y of one circle to another, NOT the radius (only the Shape part)
	 * because of static binding
	 *
	 * Circle's assignment should take in a Circle* 
	 * NOT Shape*, so even if =operator is virtual, it's not overridden
	 *
	 * Solution: write a new method that takes in a Shape*
	 * but what if its not a Circle
	 *
	 * if we had:
	 * int main () {
	 * 		Shape* p;	
	 * 		if (...)
	 * 			p = new Circle(...);
	 * 		else
	 * 			p = new Triangle(...);
	 *
	 * 		Shape* g = ???
	 * 		Shape* h = new _________ // doesn't work because the ??? has to have name of Shape
	 *
	 *		// GET THE OBJECTS TO DO THE WORK FOR US
	 *
	 *		Shape* q = p->clone();
	 * }
	 *
	 *
	 * struct Shape {
	 *	virtual Shape* clone() const = 0;
	 * }
	 * 
	 * struct Circle {
	 *     Shape* clone() const {
	 *     		return new Circle(*this); //return type can vary
	 *     }
	 * } 
	 *
	 * int main () {
	 * 		Circle* p = new Circle(...);
	 *		//Circle* q = p->clone(); still doesn;t work.. 
	 * }
	 *
	 * //change clone's return type 
	 *
	 * struct Circle {
	 * 		Circle* clone() const {
	 * 			return new Circle(*this);
	 * 		}
	 * }
	 *
	 * int main () {
	 * 		Circle* p = new Circle(...);
	 * 		Circle* q = p->clone(); //now this works!
	 * }
	 *
	 * RETURN TYPES OF VIRTUAL METHODS ARE COVARIANT
	 */
    if (const Circle* const r = dynamic_cast<const Circle*>(p))
        if (Circle* const s = dynamic_cast<Circle*>(q))
            *s = *r;
    ASSERT_EQ(*p, *q);
    delete p;
    delete q;}

TEST(Shape_Fixture, test_7) {
//  const Circle a[] = {Shape(2, 3), Circle(4, 5, 6)}; // doesn't compile
    const Shape  a[] = {Shape(2, 3), Circle(4, 5, 6)};
    ASSERT_EQ(0, a[0].area());
    ASSERT_EQ(0, a[1].area());}

TEST(Shape_Fixture, test_8) {
    const Circle a[] = {Circle(2, 3, 4), Circle(5, 6, 7)};
    ASSERT_EQ(3.14 * 4 * 4, a[0].area());
    ASSERT_EQ(3.14 * 7 * 7, a[1].area());
    const Shape* const p = a;
    ASSERT_EQ(3.14 * 4 * 4, p[0].area());
//  p[1].area();                                           // illdefined
    }
