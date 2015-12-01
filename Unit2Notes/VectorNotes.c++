#include <cstddef>

/**
 * VECTORS n CONSTRUCTORS
 */

// Constructors example
struct A {
	int _i;		//automatically we are given A(), A(A), ~A(), =(A)
	B _y;
}

int main () {
	A x;	// A(), nothing to _i, calls B()
	A y = x;	//A(A) => B(B), copies x's _i to our _i

	A z;
	x = z;	// =(A), copies z's _i to x's _i, =(B)
}
// now x, y, z die
// so ~A(), nothing to _i, ~B() 3 times (because we have 3 A's)



// Vectors constructors example 1
template <typename T>
class vector {
	private:
		A _a;
		T* _b;
		T* _e;

	public:
		vector (...) {
			 
		}

		~vector () {

		}

		vector (const vector& rhs) : /* again, this is the INITIALIZATION LIST that invokes the copy constructor */
			_a(rhs._a) {
				_b = rhs._b;
				_e = rhs._e;
		}

		vector& operator = (const vector& rhs) {
			_a = rhs._a;
			_b = rhs._b;
			_e = rhs._e;
			return *this;
		}
}

int main () {
	vector<int> x (10, 2);
	vector<int> y (20, 3);
	/**
	 * 		   __
	 *		a |__|
	 *	x:	b |_-|-----> [2, 2, 2, 2, 2, 2, 2, 2, 2, 2] (this has 10 elements)
	 *	    e |_-|-----------------------------------^ 
	 *
	 * 		   __
	 *		a |__|
	 *	y:	b |_-|-----> [3, 3, 3, 3, 3, 3, 3, 3, 3, ... , 3] (this has 20 elements)
	 *	    e |_-|-----------------------------------------^ 
	 *
	 **/
	x = y;
	/**
	 *  Now x's b points to wherever y's b points at, x's e points to where y's e points at 
	 * 		   __
	 *		a |__|
	 *	x:	b |_-|----\ [2, 2, 2, 2, 2, 2, 2, 2, 2, 2] (this has 10 elements)
	 *	    e |_-|-----\---------------------------------\
	 *					\							      \	
	 * 		   __ 		 \							   	   \	
	 *		a |__|		  V 							   V	
	 *	y:	b |_-|-----> [3, 3, 3, 3, 3, 3, 3, 3, 3, ... , 3] (this has 20 elements)
	 *	    e |_-|-----------------------------------------^ 
	 *
	 *  So now at this point, once you modify x, you also modify y
	 *
	 *  Also we've lost any way to get to x's original container (10-element array of 2's)
	 *  so at the destructor, they will both try to destroy the same array, which will lead to a SEG FAULT ):
	 **/
}

// Vectors constructors example 2
void f (vector <int> y) {

}

int main () {
	vector<int> x (10, 2);
	f(x);
	/**
	 * 		   __
	 *		a |__|
	 *	x:	b |_-|-----> [2, 2, 2, 2, 2, 2, 2, 2, 2, 2] (this has 10 elements)
	 *	    e |_-|------- ^ -------------------------^ 
	 * 		   __		 /							^
	 *		a |__|		/						   /		
	 *	y:	b |_-|-----/ 						  /
	 *	    e |_-|-------------------------------/
	 *
	 *  because at f, y's b and y's e point to the same places that x's b and x's e do,
	 *  at the end of function f (...), vector x will be destroyed. ):
	 **/
}

//Vectors constructs example 3
template <typename T>
class vector {
	private:
		_a
		_b
		_e

	public:
		vector (const vector& rhs) :
			_a(rhs._a) {
				_b = _a.allocate(rhs.size());
				_e = _b + rhs.size();
				// can't call copy() because nothing has been constructed
				my_uninitialized_copy(_a, rhs._b, rhs._e, _b); //calls Downing's my_uninitialized_copy, which constructs and copies over the contents
		}
		
		vector& operator = (const vector& rhs) {
			// gotta tear yourself down

			// stuff that usually happens in the destructor:
			my_destroy(_a, _b, _e);
			_a.deallocate(_b, size());

			//exactly like the constructor (lines 123-126)
			_b = _a.allocate(rhs.size());
			_e = _b + rhs.size();
			my_uninitialized_copy(_a, rhs._b, rhs._e, _b); 
		}

	/*** OK WHAT IF WE USED THE = OPERATOR IN THE CONSTRUCTOR?? ***/
	public:
		vector (const vector& rhs) : 
			_a(rhs._a) {
				//*this = rhs;
				// ^ that does not work because of the first two lines of the = operation
				// (aka calling my_destroy and deallocate.. will try to destroy and deallocate for 
				// a vector that has not yet been created)

				// thus we must do this first:
				_b = _e = nullptr;
				*this = rhs;
		}

		vector& operator = (const vector& rhs) {
			//same stuff from the last = operator we created
		}

	/*** OK WHAT IF WE USED THE CONSTRUCTOR IN THE = OPERATOR?? ***/
	public:
		vector (const vector& rhs) :
			_a(rhs._a) {
				//same constructor as ones from lines 123-129
		}
		
		// gotta deep-copy
		vector& operator = (vector rhs) { 
			/**
			 *  runs:
			 * 		_b = _a.allocate(rhs.size());
			 * 		_e = _b + rhs.size();
			 * 		my_uninitialized_copy(_a, rhs._b, rhs._e, _b);
			 **/
			swap(_b, rhs._b);
			swap(_e, rhs._e);
			/**
			 * rhs will die due to the destructor
			 *
			 * so now rhs._b = x's old _b,
			 * and rhs._e = x's old _e
			 *
			 * so at the end of the scope, x's old array is destroyed! 
			 **/
		}
}

//Vectors constructs example 4
vector<int> f (...) {

}

int main () {
	vector<int> x(f(...));
	/*            ^----^ is temporary/r-value
	 * x's copy constructor makes a copy of this temp
	 * "steal the data": copy the _b and _e of f() and then set its _b = _e = nullptr
	 **/
}

