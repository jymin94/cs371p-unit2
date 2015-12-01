/**
 * NOTES OVER LECTURES ON PROJECT 5
 **/

Life<ConwayCell>  x(20,20); // no dynamic binding required
Life<FredkinCell> y(30,40);

Life<AbstractCell> z(50,60); //can't have an instance of it

Life<NonAbstractCell> fuck(20,10); //there's only enough room for a ConwayCell or FredkinCell object
//you would only have the nonabstract parts

//with dynamic binding,
Life<AbstractCell*> t (70,80);

vector<ConwayCell> x(10, ConwayCell(...));
/**
 * calls the ConwayCell(...) constructor ONCE (and constructor of AbstractCell)
 * ConwayCell(ConwayCell) constructor (copy constructor), 10 times 
 * ~ConwayCell()
 **/

vector<AbstractCell> y(10, ConwayCell(...)); //does not compile

vector<AbstractCell*> y(10, ConwayCell(...));
//							^-------------^ is not AbstractCell*

vector<AbstractCell*> y(10, new ConwayCell(...));
						//  ^-----------------^ instance of child of AbstractCell
/**
 * calls ConwayCell(...) constructor once
 * but creates 10 pointers to one ConwayCell (10 copy constructors) lol
 **/

vector<AbstractCell*> y(10);
// null pointers at this point
fill(y.begin(), y.end(), new conwayCell(...));
// also creates 10 pointers to one ConwayCell i think lel

/** using a wrapper for AbstractCell* called Cell **/
int main () {
	Cell x = new ConwayCell(...);
		// Cell's constructor invoked
	Cell y = new FredkinCell(...);
		// Cell can take in an AbstractCell*
	Cell z = x;
		/**
		 * inside of Cell we have AbstractCell*
		 * copy construct of Cell called
		 * this AbstractCell* pointer will point to a brand new ConwayCell
		 * (it creates a NEW pointer and copies the content over)
		 **/
	z = y;
		// destroys the old, builds the new, and copies over the contents
}
/*
 * at this point, EVERYTHING DIES
 * Cell manages the memory for that instance of the child
 * delete is in Cell but create is in OUR code
 */

/* back to our vector issue: */
vector<AbstractCell*> x(10, new ConwayCell(...));
// as mentioned before, this creates 10 pointers to one ConwayCell still

//now we can use Cell:
vector<Cell> y (10, Cell(new ConwayCell(...)));
/**
 * calls ConwayCell(...) constructor ONCE
 * calls Cell(...) constructor ONCE
 * calls Cell(Cell) constructor (copy constructor, which calls clone()) 10 times
 * calls ConwayCell(ConwayCell) constructor (copy constructor) 10 times
 * calls ~Cell() ONCE
 * calls ~ConwayCell() ONCE
 **/

vector<Cell> z (10, new ConwayCell(...));
// compiles because Cell x = new ConwayCell(...)
// because this is not explicit
// but I think this doesn't work idk uh
