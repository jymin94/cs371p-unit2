// -----------
// Vector1.c++
// -----------

// http://www.cplusplus.com/reference/vector/vector/

#include <vector> // vector

#include "gtest/gtest.h"

#include "Vector1.h"

using namespace std;

using testing::Test;
using testing::Types;

template <typename T>
struct Vector_Fixture : Test {
    using vector_type = T;};

typedef Types<
               vector<int>,
            my_vector<int>>
        vector_types;

TYPED_TEST_CASE(Vector_Fixture, vector_types);

TYPED_TEST(Vector_Fixture, test_1) {
    using vector_type = typename TestFixture::vector_type;

    vector_type x;
	/*
	 * this tells us that the class must have a default constructor
	 */
    ASSERT_EQ(0, x.size());}
	/*
	 * obviously this tells us this class must have a size() method
	 * that takes in no arguments and returns the # of elements
	 */

TYPED_TEST(Vector_Fixture, test_2) {
    using vector_type = typename TestFixture::vector_type;

    vector_type x(3);
	/*
	 * class must have a constructor that takes in value (# of elements)
	 * general construction: default constructions for T 
	 */
    ASSERT_EQ(3, x.size());
    ASSERT_EQ(0, x[1]);
    x[1] = 2;
	/*
	 * class must have an index operator
	 * and its return type is T&, an l-value and read/write reference
	 * because it can be assigned
	 */
    ASSERT_EQ(2, x[1]);
    fill(x.begin(), x.end(), 4);
	/*
	 * class must have an iterator (forward iterator for fill() (NOT PHIL))
	 * but a VECTOR always provides a RANDOM ITERATOR!
	 * simplest type to return with this iterator: pointer aka T*
	 */
    ASSERT_EQ(4, x[1]);}

TYPED_TEST(Vector_Fixture, test_3) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(3, 2);
	/*
	 * class must have a 2-arg constructor (# of elements, value to fill with)
	 */
    ASSERT_EQ(2, x[1]);}
	/*
	 * vector from #45 is read/write 
	 * but now this vector (from line 70) is read-only
	 * so THIS index operator will be a read-only
	 * aka its return type is const T&, an r-value and a read-only
	 */ 

TYPED_TEST(Vector_Fixture, test_4) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(3, 4);
    const vector_type y(6, 4);
    ASSERT_TRUE(equal(x.begin(), x.end(), y.begin()));}
	/* returns a READ-ONLY iterator (aka const T*) */
