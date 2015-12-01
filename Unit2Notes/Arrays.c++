// ----------
// Arrays.c++
// ----------

#include <algorithm> // copy, count, equal, fill
#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <iostream>  // cout, endl
#include <string>    // string
#include <vector>    // vector

using namespace std;

struct A {
    int i; /* one instance of type A is 4 bytes bc of int i */

    string f () {
        return "A::f";}};

struct B : A {
    int j; /* one instance of type B is 8 bytes bc it inherits from A */

    string f () {
        return "B::f";}};

void f1 (int p[]) {
    assert(sizeof(p) == 8); // warning: sizeof on array function parameter will return size of 'int *' instead of 'int []' [-Wsizeof-array-argument]
    ++p;
    ++p[0];
    ++*p;}

void f2 (int* p) {
    assert(sizeof(p) == 8);
    ++p;
    ++p[0];
    ++*p;}

int main () {
    cout << "Arrays.c++" << endl;

    {
    int a[] = {2, 3, 4};
    assert(*a            == a[0]);
    assert(a             == &a[0]);
    assert(sizeof(a)     != sizeof(&a[0]));
    assert(sizeof(a)     == 12);
    assert(sizeof(&a[0]) == 8);
//  ++a;                                    // error: lvalue required as left operand of assignment
    ++a[0];
    assert(*a   == 3);
//  assert(a[3] == 0);                      // undefined
    }

    {
    const size_t s    = 10;
    const int    a[s] = {2, 3, 4};
    assert(sizeof(a) == 40);
    assert(a[1]      ==  3);
    assert(*(a + 1)  ==  3);
    assert(a[s - 1]  ==  0);
//  ++a;                           // error: lvalue required as left operand of assignment
//  ++a[1];                        // error: increment of read-only location
    }

    {
    const size_t s = 10;
//  const int    a[s];       // error: uninitialized const 'a'
    int a[s];
    assert(sizeof(a) == 40);
//  assert(a[0]      ==  0); // undefined
    }

    {
    const size_t s    = 10;
    const int    a[s] = {};
    assert(sizeof(a) == 40);
    assert(a[0]      ==  0);
    }

    {
    int a[] = {2, 3, 4};
    assert(a[1] == 3);
    f1(a);
    assert(a[1] == 5);
    f2(a);
    assert(a[1] == 7);
    }

    {
    int        a[] = {2, 3, 4};
//  int        b[] = a;             // error: initializer fails to determine size of 'b'
    int* const b   = a;
    assert(a         == b);
    assert(sizeof(a) != sizeof(b));
    assert(sizeof(a) == 12);
    assert(sizeof(b) ==  8);
    ++a[1];
    assert(a[1] == 4);
    assert(b[1] == 4);
    }

    {
    int          a[] = {2, 3, 4}; /* created on the stack */
    const size_t s   = sizeof(a) / sizeof(a[0]);
    int b[s]; 					/* also created on the stack */
    copy(a, a + s, b);
    assert(a != b);
    assert(equal(a, a + s, b));
    ++a[1];
    assert(a[1] == 4);
    assert(b[1] == 3);
    }

    {
    int a[] = {2, 3, 4}; /* also created on the stack */
    int b[] = {5, 6, 7}; /* also created on the stack */
//  b = a;                                     // error: invalid array assignment
    const size_t s = sizeof(a) / sizeof(a[0]);
    copy(a, a + s, b); /* only works because the arrays are the same size */	
    assert(a != b);
    assert(equal(a, a + s, b));
    ++a[1];
    assert(a[1] == 4);
    assert(b[1] == 3);
    }

    {
    const ptrdiff_t  s = 10;
    const int        v =  2;
          int* const a = new int[s]; 
	/* this array is now on the HEAP aka we don't have to know the size of it at compile time
	 * if we had:
	 * int s;
	 * cin >> s;
	 * int a[s]; //this line doesn't compile because you need to know the size at compile time.
	 *
	 * also this line is CONSTANT effort
	 * but instead of int, if it was "elephant", it would be linear effort because we need to run the initializer for elephant.
	 *
	 * you can't pass arrays to functions- only pointers.
	 * 	so it doesn't matter whether it's on the heap or the stack
	 **/
    assert(sizeof(a) == 8);
    fill(a, a + s, v);
    assert(count(a, a + s, v) == s);
    assert(a[1] == v);
    f1(a);
    assert(a[1] == v + 2);
    f2(a);
    assert(a[1] == v + 4);
    delete [] a;
	/**
	 *	this has 10 ints.. does it matter if it had 10 or 1000?
	 *  this is CONSTANT EFFORT because it's ints
	 *  but instead of int, if it was "elephant", it would be linearn effort because we need to call the destructor for each.
	 **/

	/**
	 * what if this just said "delete a"?
	 * then the compiler will think it's just pointing to one int/elephant
	 * it will deallocate everything though (heap manager takes care of that, not the user)
	 * will just keep invoking the wrong number of destructors
	 **/
    }

    {
    const size_t     s = 10;
    const int        v =  2;
          int* const a = new int[s];
    assert(sizeof(a) == 8);
    fill(a, a + s, v);
    int* const b = a;	/* not building another array, just copying the address */
    assert(&a[1] == &b[1]);
    int* const x = new int[s]; /* made a copy */
    copy(a, a + s, x);
    assert( a[1] ==  x[1]);
    assert(&a[1] != &x[1]);
    delete [] a;
    delete [] x;
    }

    {
    const size_t     s = 10;
    const int        v =  2;
          int* const a = new int[s];
    assert(sizeof(a) == 8);
    fill(a, a + s, v);
    int* b = new int[s];
    fill(b, b + s, v);
//  b = a;                           // memory leak
	/*
	 * assigning the pointer
	 * you lose original address of the original array.. leads to memory leak
	 *
	 * if sizeof(b) < sizeof(a) then delete b, THEN build a new array and copy
	 */
    copy(a, a + s, b);
    assert( a[1] ==  b[1]);
    assert(&a[1] != &b[1]);
    delete [] a;
    delete [] b;
    }

    {
	/*
	 * remember: one instance of A is 4 bytes, one instance of B is 8 bytes
	 */

	/*
	 * by saying "struct A { };" we get for free:
	 * A(); //default constructor
	 * ~A(); //destructor
	 * A(A); //copy constructor
	 * =(A); //copy assignment
	 */

//  B a[] = {A(), A(), A()};    // error: conversion from "A" to non-scalar type "B" requested
	/*
	 * this says each object will be 8 bytes
	 * but each of the A() are 4 bytes 
	 */
    A a[] = {B(), B(), B()};    // slice
	/* 
	 * this says each object will be 4 bytes
	 * but each of the B() are 8 bytes each -> so only the "A" part of B will be spliced into this array 
	 *
	 * so we get:
	 * A(); //3 times
	 * B(); //3 times
	 * A(A) //3 times, only works because B is an A
	 *  ^ this is when we downcast the B to A objects
	 * ~B(); //3 times
	 * ~A(); //3 times
	 *
	 *  NET EFFECT: built 3 A's
	 */
    assert(a[1].f() == "A::f");

    }

    {
//  int*    const a = new double[10]; // error: cannot convert 'double*' to 'int*    const' in initialization
//  double* const a = new int[10];    // error: cannot convert 'int*'    to 'double* const' in initialization
    }

    {
//  B* const a = new A[10];                      // error: invalid conversion from ‘A*’ to ‘B*’
    A* const a = new B[10];                      // dangerous
	/*
	 * THIS IS D A N G E R O U S D: D:
	 * it's like building an array of tigers and pointing to it using a pointer of mammals 
	 */
    assert(a[0].f() == "A::f");
	/*
	 * type of a: pointer to A
	 * so it's a pointer to an index operator
	 * a[i] = size of type of pointer of A
	 */
//  assert(a[1].f() == "A::f");                  // undefined
	/*
	 * so THIS ^ doesn't work because we're stepping at the wrongly-sized steps
	 * so we're not at the edge of a size B
	 */

//  delete [] a;                                 // undefined
    assert(static_cast<B*>(a)[1].f() == "B::f");
    delete [] static_cast<B*>(a);                // ~B::B() and ~A::A()
    }

    {
    const size_t      s = 10;
    const int         v =  2;
	/*
	 * T* a = new T[s]; // T() aka default constructor, s times
	 * fill(a, a+s, v);	// =(T), s times
	 * // 2 linear efforts ^
	 *
	 * T* b = new T[s];	// T()
	 * copy(a, a+s, b); // =(T)
	 *
	 * //Stack or heap don't give fill/copy semantics
	 * T* c = new T[2 * s];
	 * fill(c, c+(2*s), w);
	 *
	 * ALL DIS SHIT UP HERE IS NASTY SO WE DO:
	 */
		  vector<int> x(s, v);
	/*
	 * calls T(T), s times
	 * 1 linear pass + gets values in there
	 */

	/*
	 * vector<T> y = x;
	 * 	// builds new array, copies values
	 *  // calls T(T), s times
	 *  // 1 linear pass
	 */

    assert(x.size() == s);
    assert(x[0]     == v);
    vector<int> y(x);
	/*
	 * builds new array, copies values
	 * calls T(T), s times
	 * 1 linear pass
	 */  
    assert( x ==  y);
    assert(&x != &y);
    vector<int> z(2 * s, v);
	/*
	 * T(T), 2*s times
	 */
    x = z;
	/*
	 * x is not big enough..
	 * so ~T() (destructor) invoked s times
	 * now copy constructor of x
	 */
    assert( x ==  z);
    assert(&x != &z);
    }

    {
//  vector<A>* const p = new vector<B>; // error: cannot convert 'vector<B, allocator<B> >*' to 'vector<A, allocator<A> >* const' in initialization
    }

    cout << "Done." << endl;
    return 0;}
