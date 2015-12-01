struct A {
	virtual void f() {
	
	}
	/**
	 *	if declared virutal at the top, remains virtual all the way down
	 **/

	void f(int) {

	}
	/* can be overloaded */
	
	void g() {

	}
};

struct B : A {
	void f() {

	}

	void g() {

	}
};

struct C : B {
	void f () {

	}
};

int main () {
	A* p;
	if (...)
		p = new B;
	else
		p = new C;

	//*p.f()	// doesn't compile
	(*p).f() or p->f();
	/* dynamic binding to get the correct f() */
	
	p->g();
	p->f(2);
	/**
	 * static binding; meanings don't change
	 * solely based on the type of the pointer
	 **/
}


/* Example 1 */
struct A {
	void f () {

	}
};

struct B : A {
	virtual void f () {

	}
};

struct X : B {
	void f () {

	}
}

int main () {
	A* p = new X;
	p->f(); 	// calls A::f()

	B* pq = new X;
	pq->f();	// calls X::f()
}

/* Example 2 */
int main () {
	A* p;
	if (...)
		p = new B;
	else if (...)
		p = new X;
	else
		p = new C;

	p->f();
}

/* 
 * Downing drew a really good diagram for this lel
 *
 * but basically every time there is a new "virtual", we add a pointer of the type of the new thing in the children
 * yea idk
 */


/* INLINE FUNCTIONS: replacing call to function with the body of the function
 *
 * CAN WE INLINE VIRTUAL METHODS?
 * p->f()
 *
 * NO
 */

int main () {
	B x;
	x.f();

	A* p = new B;
	p->A::f();

	/*
	 * Assuming we got
	 * A:A() {
	 *    f()	//calls A's f()
	 * }
	 */
	A* p = new C;	// calls A(), B(), C()
	p->f();			// calls C's f()

	/* at the end calls ~C(), ~B(), ~A()
}
