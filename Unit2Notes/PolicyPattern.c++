/*
 * Also notes for 10/21 on Policy Design Patterns
 */

Stack<T> x; //LIFO

/* 3 types of backing containers that manage a sequence and have ways to traverse through it?
 * VECTOR
 * DEQUE
 * LIST
 */

/* VECTOR
 *   maintains an array
 *   in front-loaded fashion 	[*, *, *, *, , , , ,]
 *   adding to front: O(n)
 *   adding to back: O(1) but amortized (because if vector fills up you must expand
 */

/* DEQUE
 * 	 middle-loaded
 * 	 adding to front and back: amortized O(1)
 * 	 because to grow the array, it'll take linear effort
 */

/* LIST
 *   adding to the front and back: O(1) 
 */

Stack<T> x; //LIFO
Stack<T, vector<T>>;
Stack<T, deque<T>>;
Stack<T, list<T>>;

queue<T> y; /* FIFO push is always push-back */
queue<T, vector<T>>; /* Doesn't work because with vector it's too expensive to pop front*/
queue<T, deque<T>>; 
queue<T, list<T>>;

priority_queue<T> q;
/* binary heap: mapping of tree into array 
 * O(log n) performance if you move through the array (O(n))
 */
priority_queue<T, list<T>> /* doesn't work because you have to be able to hop around it in constant time */
