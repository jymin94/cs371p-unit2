/*
 * When initialized with defined types like int, the container has constant effort
 * and the array elements are not initialized to anything
 *
 * but if we initialize with a user-defined type, it takes LINEAR effort because 
 * we have to run the initializer for each element
 *
 */
// --------------------
// FunctionDefaults.c++
// --------------------

// http://www.cplusplus.com/doc/tutorial/functions2/

#include <cassert>  // assert
#include <iostream> // cout, endl

/*
 * when declaring a method and we want to default some of the arguments,
 * you have to put it in the trailing characters
 */
int f (int i, int j, int k = 4);

void g1 () {
//  assert(f()        ==  9);  // error: too few arguments to function "int f(int, int, int)"
//  assert(f(2)       ==  9);  // error: too few arguments to function "int f(int, int, int)"
    assert(f(2, 3)    ==  9);
    assert(f(2, 3, 5) == 10);}

/* this is where we define the f that we DECLARED up at #18
 *                      THIS v was already defaulted 
 * and since we're defaulting s here,
 * we can now call f with just one argument 
 * e.g. f(2)
 */
int f (int r, int s = 3, int t) {
    return r + s + t;}

void g2 () {
//  assert(f()        ==  9);  // error: too few arguments to function "int f(int, int, int)"
    assert(f(2)       ==  9);
    assert(f(2, 3)    ==  9);
    assert(f(2, 4, 5) == 11);}

/*
 * NOW we can just call f with no arguments
 * e.g. f()
 */
int f (int x = 2, int y, int z);

/*
 * in my notes I wrote "COMBINATION OF DIFFERENT HEADER FILES!" but idk why
 */
void g3 () {
    assert(f()        ==  9);
    assert(f(3)       == 10);
    assert(f(3, 4)    == 11);
    assert(f(3, 4, 5) == 12);}

/*
 * Overloading a function: we can have 2 different versions of the function
 * by having either different number of arguments
 * or having a different type of argument
 */
int h (int i) {
    return i;}

/* 
 * compiler's gonna freak out.. WHICH h(...) to call?!?!
 */
int h (int i, int j = 0) {
    return i + j;}

//int x (int i, int j = i) { // error: default argument references parameter 'i'
//    return i + j;}

int main () {
    using namespace std;
    cout << "FunctionDefaults.c++" << endl;

    g1();
    g2();
    g3();

//  h(10);                   // error: call to 'h' is ambiguous
    assert(h(11, 12) == 23);

    cout << "Done." << endl;
    return 0;}
