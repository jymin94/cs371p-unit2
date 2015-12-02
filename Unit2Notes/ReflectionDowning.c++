/*
 * Downing has a lot of notes on Reflection lel
 * Notes 11/23 
 * 
 * MAP
 */

vector<int> x (10,2);
	// size of the underlying array = 10
	// size of vector = 10

push_back(3);
	// creates a new array (probably of twice the size of original array)

map<string, int> m;
// key: string, value: int
map<string, int>::value_type v("abc",2);
map<string, int>::key_type k = "abc";
map<string, int>::mapped_type v = 2;
map<string, int>::value_type p(k,v);
m.insert(p);

cout << m["abc"];	//output is 2, mapped_type

q = m.find("abc");
// returns an iterator 

//aka
map<string, int>::iterator q = m.find("abc");
if (q == m.end()) //didn't find it
	...

// iterates over the key, value
cout << q->first; //"abc"
cout << q->second; //2


// --------------
// Reflection.c++
// --------------

// http://www.cplusplus.com/reference/memory/shared_ptr/

#include <string> // string
#include <memory> // shared_ptr

#include "gtest/gtest.h"

#include "Reflection.h"

using namespace std;

struct A {
    virtual string f () = 0;};

struct B : A {
    static Reflection<A> r;
	/* inherited from A
	   DECLARED static
   	*/	   

    string f () {
        return "B::f()";}};

Reflection<A> B::r("B", shared_ptr<A>(new B));
// populating the map with names of the instances and actual instances of that class

struct C : A {
    static Reflection<A> r;

    string f () {
        return "C::f()";}};

Reflection<A> C::r("C", shared_ptr<A>(new C));
/* the shared_ptr is empty at first (?!?)
 * this registry needs to run before main
 * (initializes static in a constructor (done in Reflection.h)
 */

TEST(Is_Prime_Fixture, test_1) {
    shared_ptr<A> p = Reflection<A>::only().find("B")->second;
	/*
	 * returns the one and only map in "find"
	 */
    ASSERT_EQ("B::f()", p->f());}

TEST(Is_Prime_Fixture, test_2) {
    shared_ptr<A> p = Reflection<A>::only().find("C")->second;
    ASSERT_EQ("C::f()", p->f());}

/* k putting Reflection.h here */
// ------------
// Reflection.h
// ------------

#ifndef Reflection_h
#define Reflection_h

#include <map>    // map
#include <memory> // shared_ptr
#include <string> // string

template <typename T>
struct Reflection {
    using map_type   = std::map<std::string, std::shared_ptr<T>>;
    using value_type = typename map_type::value_type;

    Reflection (const std::string& k, std::shared_ptr<T> v) {
        only().insert(value_type(k, v));}

	/*
	 * one local static map
	 */
    static map_type& only () {
        static map_type only;
        return only;}};

#endif // Reflection_h
