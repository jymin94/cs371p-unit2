/*
 * Semantics of variables in c++:
 * 1) How many are there?
 * 2) When are they allocated?
 * 3) When are they initialized?
 * 4) What is their lifetime?
 * 5) What is their scope?
 */

void f() {
	...
	int l = g(...);
	...
}

/*
 * int l
 *
 * 1) one per call to f()
 * 2) when f() is called
 * 		can multiple l's coexist? YES, if recursive
 * 3) asking "when does g() run": when we get to line 12 lol
 * 4) lifetime of call to f()
 * 5) as soon as DECLARED, inside f()
 */

void f() {
	static int l = g(...);
}

/*
 * static int l
 *
 * 1) just ONE
 * 2) when the program starts running (independent of f())
 * 3) at the first call to f() (because g() runs just once)
 * 4) entire program (ends when program ends)
 * 5) still in f()!!
 */

void f() {
	static int l = 0;
	++l;
	return l;
}
/* 1st call returns 1
 * 2nd call returns 2
 * 3rd call returns 3
 * like a memory function
 */

//foo.c++
int g = h(...);

//bar.c++
int m() {
	++g;
}

/*
 * int g
 *
 * global variable
 * 1) just ONE
 * 2) beginning of the program
 * 3) beginning of the program
 * 	  (sets up shit that needs to be true before main)
 * 5) global scope
 */

//bar.c++
extern int g; //doesn't compile.. idk why

int m() {
	++g;
}

//foo.c++
static int g = h(...);
/* scope changed from global to FILE scope (only in foo.c++) */

//bar.c++
extern int g;
int m() {
	++g; //still compiles but linking fails
}

/*
 * so if you add "static" to a local, SCOPE DOESN'T CHANGE
 * if you add "static" to global, ONLY SCOPE CHANGES
 */


// in Java
class A {
	int i;
	static int ci; // just one 
}

class A<T> {
	T i;
	//static T ci;	//ONE still
	/* ^ this line is not possible for STATIC */
}

// in c++
// in A.h
template <typename T>
class A {
	//int i;	//one for every instance of A
	T i;
	//static int ci;		
	static T ci; // one per T
	/* allowed in c++, also is the DECLARATION of this variable */
}

//foo.c++
int g = h(...);	/* DEFINITION, only one of these */

//bar.c++
extern int g;	/* DECLARATION, many possible */

// in A.c++
template <typename T>
T A<T>::ci(...); //DEFINITION
