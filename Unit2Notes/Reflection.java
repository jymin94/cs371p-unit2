/*
 * Turning an external representation into an instance of a class 
 */
class A { } //builds instance of class class

class B { } 

class T {
	public static void main (String [] args) {
		A x = new A();

		class c1 = A.class;
		/* this is static because we didn't need an instance of A */

		//A x = c1.newInstance();
		/* method of class c1
		 * return type = Object
		 * doesn't compile..
		 */

		A x = (A)c1.newInstance();
		// A() better exist & be public
		// if A was abstract class or Interface, we wouldn't be able to have an instance of it
		// can't have A() if it doesn't have one
		// if we wrote our own constructor, then default A() disappears

		class c2 = x.getClass();
		// x is an A
		// "getClass()" belongs to class A, but really belongs to Object (inherited)
		// return type = Class

		A y = (A)c2.newInstance();
		//There's a registry (map) of all the things class has..
		//key: name
		//value: instances of class class

		class c3 = class.forName("A");
		// static method of class 
		// return type = class

		A z = (A)c3.newInstance();
	}
}

// ---------------
// Reflection.java
// ---------------

abstract class A  {
    public abstract String f ();}

class B extends A {
    public String f () {
        return "B.f()";}}

class C extends A {
    public String f () {
        return "C.f()";}}

final class Reflection {
    public static void main (String[] args) {
        System.out.println("Reflection.java");

        try {
            A x = (A) Class.forName("B").newInstance();
			/* getting Class class instance of B, then get new Instance of B
			 * which returns an Object
			 * then casted to parent A
			 */
            assert x.f().equals("B.f()");}
			/*
			 * proves dynamic binding exists for Java
			 */
        catch (ClassCastException e) {
            assert false;}
        catch (ClassNotFoundException e) {
            assert false;}
        catch (IllegalAccessException e) {
            assert false;}
        catch (InstantiationException e) {
            assert false;}

        try {
            A x = (A) Class.forName("C").newInstance();
            assert x.f().equals("C.f()");}
        catch (ClassCastException e) {
			/* ClassCastException happens if we didn't have C as a child of A */
            assert false;}
        catch (ClassNotFoundException e) {
			/* ClassNotFoundException happens if no C exists in registry */
            assert false;}
        catch (IllegalAccessException e) {
			/* IllegalAccessException happens if default constructor of C is protected/private (for newInstance c) */
            assert false;}
        catch (InstantiationException e) {
			/* InstantiationException happens if C were an abstract class, interface,
			 * or does not have a default constructor at all */
            assert false;}

        System.out.println("Done.");}}
