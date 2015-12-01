// -------
// Stack.h
// -------

// http://www.cplusplus.com/reference/stack/stack/

#ifndef Stack_h
#define Stack_h

#include <cassert> // assert
#include <utility> // !=, <=, >, >=

using namespace std::rel_ops;

template <typename T, typename C = std::deque<T>>
class my_stack {
    public:
        typedef C                                         container_type;

        typedef typename container_type::value_type       value_type;
        typedef typename container_type::size_type        size_type;

        typedef typename container_type::reference        reference;
        typedef typename container_type::const_reference  const_reference;

    public:
        friend bool operator == (const my_stack& lhs, const my_stack& rhs) {
            return lhs._c == rhs._c;}

        friend bool operator < (const my_stack& lhs, const my_stack& rhs) {
            return lhs._c < rhs._c;}

    private:
        container_type _c;

    public:
		/* So let's create a default constructor:
		 * my_stack(const C& c = C()) { //this notation means if there's no c provided, it will call the default no-argument constructor
		 * 		_c = c;	
		 * }
		 * ^ this creates an empty c using the default constructor and then calls on the assignment operator
		 * if we use an INITIALIZATION LIST, then we can assign _c to the passed in c BEFORE this constructor runs, so that all we end up doing is calling the default constructor with a known value for _c.
		 **/
        explicit my_stack (const container_type& c = container_type()) :
                _c (c) 
            {}

        // Default copy, destructor, and copy assignment.
                  my_stack   (const my_stack&) = default;
                  ~my_stack  ()                = default;
        my_stack& operator = (const my_stack&) = default;

        bool empty () const {
            return _c.empty();}

        void pop () {
            _c.pop_back();}

        void push (const_reference v) {
            _c.push_back(v);}

        size_type size () const { /* the const is there because our stack will not be modified through this method */
            return _c.size();}

        reference top () { /* this is the read/write top () method */
            return _c.back();}

        const_reference top () const { /* this is the read-only top () method */
            return _c.back();}};

#endif // Stack_h
