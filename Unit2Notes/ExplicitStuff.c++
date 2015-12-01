/*
 * Notes for 10/23
 * 
 * When "explicit" is not added to the constructor, it implicitly converts from the types of its parameters to the types of its class ("converting constructor")
 */

struct A {
	/* by overloading the empty constructor, we lost the default constructor */
	A (int) {}
};

void f (A y) {

}

void g (vector<int> y) {

}

int main () {
	A x = 2;
	f(x);	// invokes A(A)
	f(A(3));	// A(int), A(A) (temp), ~A() (when the copy dies) 
				// net effect is just A(int)

	f(4);	// creates an A(4)! all that was required was just an int
			// A(int)
	
	vector<int> x (10000);
	g(x);	// makes a copy of vector x
	g(10000);	// if vector has a constructor with 1 int argument, this will compile.. and we don't want it to.

	/* solution: ADD EXPLICIT*/

}

/* ADD EXPLICIT */

struct A {
	explicit A (int) {

	}
};

void f (A y) {

}

void g (vector<int> y) {

}

int main () {
	//A x = 2;	//fails now
	A x(2);

	f(x); 	// invokes A(A)
	f(A(3)); // A(int), A(A) (temp), ~A() (when the copy dies)
			 // net effect is just A(int)
	
	//f(4);		//fails now
	vector<int> x (10000);
	g(x); 	// makes a copy of vector x
	//g(10000);	//now fails
}
