/*
 * Notes for 10/23
 *
 * FRIENDS
 *  1. Who can make the friend declaration? a CLASS
 *  2. Who can be made a friend? a CLASS, METHOD, or FUNCTION
 *  3. Friendship is NOT symmetric
 *  4. Friendship is NOT transitive (e.g. A <-> B <-> C, doesn't imply A <-> C)
 *  5. Privilege acquired: access to EVERYTHING
 */

class A {
	private:
		int _i;
	public:
		A (int i) {
			_i = i;
		}
}

int main () {
	A x = 2;
	A y = 2;
	cout << (x == y);	/* doesn't compile because == operator needs to be overloaded*/

	/* when overloading the operator, it can either be:
	 *   METHOD: member of class A
	 *   FUNCTION: not in the class
	 */

	cout << x.operator==(y);
	cout << (x == 2);	/* compiles because the 2 --> A(2)
						   unless the constructor was declared explicit */
	cout << (x.operator(2));
}

/* if we made the == operator a METHOD */
class A {
	private:
		int _i;
	public:
		A (int i) {
			_i = i;
		}

		/* "const A&" to protect the passed in parameter
		 * so if we called "x.operator==(y)", it protects y
		 */
		bool operator == (const A& rhs) const {
			return _i == rhs._i;
		}
}

int main () {
	const A x = 2; //possible because of the last "const" in the operator overloading
	const A y = 2;
	cout << x.operator==(y);
	// y is protected from any changes
	
	cout << (2 == x);	/* doesn't compile because it's like saying "2.operator(x)" */
	/* thus, making it a METHOD is unattractive because of the asymmetric way of behavior */
}

/* if we made the == operator a FUNCTION */
class A {
	private:
		int _i;
	public:
		A (int i) {
			_i = i;
		}
}

bool operator == (const A& lhs, const A& rhs) const {
	/* that last const is in there to protect the object when it's called */
	return lhs._i == rhs._i;
	/* PROBLEM: we can't access _i
	 * 
	 * We could:
	 * 		make _i public
	 * 		or use FRIEND
	 */
}

/* making the operator a FRIEND */
class A {
	friend bool operator == (const A& lhs, const A& rhs) {
		return lhs._i == rhs._i;
	}

	/* what if we forgot the "friend" keyword?
	 *
	 * then it will fail because it's not a binary operation (?)
	 */

	/* what if we put in a const:
	 * friend bool operator == (const A& lhs, const A& rhs) const {
	 * 
	 * then it will fail because that const is only for METHODS, and this is a FUNCTION. */
}

int main () {
	/* now we can do: */
	cout << operator==(x,y);
	cout << operator==(x,2);
	cout << operator==(2,x);
}
