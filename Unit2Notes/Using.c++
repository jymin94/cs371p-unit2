/*
 * Notes for 11/16
 */

struct A {
	void f (int) {

	}
};

struct B : A {
	void f (string) {

	}
};

int main () {
	B x;
	x.f(2);		
		/* doesn't compile!!
		 * looks for an f(), stops when it sees a "void f"
		 * and then bitches
		 * i mean it doesn't commpile
		 */

	/* 
	 * This runs in Java btw
	 * Sample scenario: what if A had like 873827635 parents?
	 * then it would have run in Java and just run the wrong one
	 * instead of breaking at COMPILE TIME which is what c++ does
	 */ 
}

/* now make this shit work by adding "using" */

struct A {
	void f (int) {

	}
};

struct B : A {
	using A::f;		/* includes everything above A also */

	void f(string) {

	}
};

int main () {
	B x;
	x.f(2); 	// now it compiles!
}
