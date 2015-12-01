/**
 * STACKS ON STACKS ON STACKS 
 * 
 * In Java, Stack at first extended Vector 
 * ^ THIS WAS BAD because by doing so, it was providing more functionalities than were needed for a Stack 
 * (e.g. inserting into the middle)
 *
 * In C++, Stack uses a backing container, as we will see in Stack.c++
 *     DEFAULT BACKING CONTAINER: deque
 */

// ---------
// Stack.c++
// ---------

// http://www.cplusplus.com/reference/stack/stack/

#include <cassert> // assert
#include <list>    // list
#include <stack>   // stack
#include <vector>  // vector

#include "gtest/gtest.h"

#include "Stack.h"

using namespace std;

using testing::Test;
using testing::Types;

template <typename T>
struct Stack_Fixture : Test {
    typedef T stack_type;};

typedef Types<
            stack<int>, 		   /* default backing container is a deque */
            stack<int, list<int>>, /* this means the backing container for this stack is a list<int> */
            stack<int, vector<int>>,
            my_stack<int>,
            my_stack<int, list<int>>,
            my_stack<int, vector<int>>>
        stack_types;

TYPED_TEST_CASE(Stack_Fixture, stack_types);

TYPED_TEST(Stack_Fixture, test_1) {
    typedef typename TestFixture::stack_type stack_type;

    stack_type x;
    ASSERT_TRUE(x.empty());
    ASSERT_EQ(x.size(), 0);

    x.push(2);
    x.push(3);
    x.push(4);
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(x.size(), 3);
    ASSERT_EQ(x.top(),  4);

    x.pop();
    ASSERT_EQ(x.size(), 2);
    ASSERT_EQ(x.top(),  3);

    x.top() = 4; 		/* the method top() returns an l-value, so it can be changed in place. */
    ASSERT_EQ(x.top(),  4);}

TYPED_TEST(Stack_Fixture, test_2) {
    typedef typename TestFixture::stack_type stack_type;

    stack_type x;
    x.push(2);
    x.push(3);
    x.push(4);
    x.top() = 5;
    ASSERT_EQ(x.top(), 5);

    const stack_type& r = x; /* because x itself is not const, we created r to do read-only of the information x has */
//  r.top() = 6;             // error: member function 'push' not viable: 'this' argument has type 'const stack_type'
	/* ^ so now this fails because there are two different type of top () methods:
	 * 		1) one that returns a read/write reference
	 * 		2) one that returns a read-only reference
	 */
    ASSERT_EQ(r.top(), 5);}

TYPED_TEST(Stack_Fixture, test_3) {
    typedef typename TestFixture::stack_type stack_type;

    stack_type x;
    x.push(2);
    x.push(3);
    x.push(4);

    stack_type y = x; 
	/* stack has a copy constructor
	 * "struct A { }" gives us A(), ~A(), =(A), A(A)
	 * so it will call the backing container's constructors and destructors
	 * begins to fail if we don't just have objects (can't trivially copy a pointer)
	 */
    ASSERT_EQ(y, x);

    y.pop();
    ASSERT_EQ(x.size(), 3);
    ASSERT_EQ(x.top(),  4);
    ASSERT_EQ(y.size(), 2);
    ASSERT_EQ(y.top(),  3);}

TYPED_TEST(Stack_Fixture, test_4) {
    typedef typename TestFixture::stack_type stack_type;

    stack_type x;
    x.push(2);
    x.push(3);
    x.push(4);

    stack_type y;
    y.push(5);
    y.push(6);

    y = x;
	/* stack has an assignment operator */
    ASSERT_EQ(y, x);

    y.pop();
    ASSERT_EQ(x.size(), 3);
    ASSERT_EQ(x.top(),  4);
    ASSERT_EQ(y.size(), 2);
    ASSERT_EQ(y.top(),  3);}

TYPED_TEST(Stack_Fixture, test_5) {
    typedef typename TestFixture::stack_type stack_type;

    stack_type x;
    x.push(2);
    x.push(3);
    x.push(4);

    stack_type y;
    y.push(2);
    y.push(3);
    y.push(4);

    ASSERT_FALSE(x != y);
    ASSERT_FALSE(x <  y);
    ASSERT_FALSE(x >  y);
    ASSERT_TRUE (x <= y);
    ASSERT_TRUE (x >= y);}
