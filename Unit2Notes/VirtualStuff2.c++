/*
 * Notes from week of 11/16
 */

/* Overriding virtual functions has to follow the EXACT syntax in order to keep dymanic binding on */
struct A {
	virtual void f (int) {
		/* keyword "virtual" turns on dynamic binding */
	}
};

struct B : A {
	void f (int) {

	}
};

int main () {
	A* p = new B;
	p->f(2);	// calls B's f()
}

/* ok now what if B's f turned into g? */
struct A {
	virtual void f (int) {

	}
};

struct B : A {
	void g (int) {

	}
};

int main () {
	A* p = new B;
	p->f(2);	//calls A's f() because B doesn't have an f()
}

/* What if B had an f again but A's f now takes in a long? */
struct A {
	virtual void f (long) {

	}
};

struct B : A {
	void f (int) {

	}
};

int main () {
	A* p = new B;
	p->f(2);	/* calls A's f() because now DYNAMIC BINDING HAS TURNED OFF */
	/* 
	 * When overriding, the nature of the method has to be EXACTLY THE SAME 
	 *
	 * so in effect, this is the equivalent of B having a g (int)
	 */
}


/* Purpose of abstract classes */

struct A { };

struct B : A { };

/*
 * 1) In order to change behavior of only B objects: change B
 * 2) In order to change behavior of A and B objects: change A
 * 3) In order to change behavior of only A objects: ?!?!?!??!
 */

// we could have an A' that is parent of A
struct A' { };

struct A : A' { };

struct B : A { };

/* Constructors in abstract classes & their inheritance */
//class shape {
struct shape {
	...
	shape (...)
	...
};

class triangle : public shape {

};
/* will not compile 
 * because it needs to call the default constructor of shape
 * but shape doesn't have one
 */

class triangle : public shape {
	triangle (...) {

	}
};

int main () {
	triangle x(...);
	cout << x.area(); //Shape's area called
}

/* 
 * RULES IN ABSTRACT CLASSES 
 *
 * 1) if A becomes an abstract class,
 * 		- can't make an instance of A (e.g. no "A x" or "new A")
 * 		- can still have data
 * 		- can have constructor (to initialize A's data)
 * 		- basicaly everything else about a class is the same
 *
 * 2) B MUST DEFINE f() OR also become abstract
 *
 * 3) Definition of f() in A() becomes OPTIONAL
 *
 */
struct A {
	virtual void f (int) = 0;	// makes this a pure virtual method
	/* also makes A an abstract class, aka cannot have an instance of A */

	/* definition here is OPTIONAL in c++ (prohibited in Java)
	 *
	 * benefit of definition of f in A: what if we had a shit ton of children of A?
	 */
};

struct B : A {
	void f (int) {

	}
};

int main () {
	A* p = new B;
	p->f(2);
	delete p;
}

/* what if B didn't override f() */
struct A {
	virtual void f (int) = 0;
};

struct B : A {
	void g (int) {

	}
	/* now class B becomes abstract by not overriding f() */
};

int main () {
	// A* p = new B; //now this does not compile
}

/* PURE VIRTUAL DESTRUCTOR?
 *
 * 1) Still can't have an instance of A
 * 2) B does not HAVE to define ~B() because a ~B() will be made FOR YOU if not defined
 * 3) Definition of ~A() is NOT optional.. child destructor always calls the parent's destructor.*/
struct A {
	virtual ~A() {

	}

	virtual void f(int) {

	}
};

struct B : A {
	void f(int) {

	}
};

int main () {
	A* p = new B;
	p->f(2);
	delete p;	// only calls ~A()
}

/* if we make the destructor PURE VIRTUAL */
struct A {
	virtual ~A() = 0;
	virtual void f(int) {

	}
};

struct B : A {
	void f(int) {

	}
};

int main () {
	A* p = new B;
	p->f(2);
	delete p;	//now calls destructor of B and A
}

/* ALSO if you choose to/must define a function, it has to happen OUTSIDE of the class. */
struct A {

}

void A::f(int) {

}

A::~A() {

}
