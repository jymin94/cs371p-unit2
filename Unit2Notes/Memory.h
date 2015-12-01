// --------
// Memory.h
// --------

#ifndef Memory_h
#define Memory_h

template <typename A, typename BI>
BI my_destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
		/* we want to be able to destroy an e of ANY kind */	
        a.destroy(&*e);}
    return b;}

template <typename A, typename II, typename BI>
BI my_uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;}}
    catch (...) {
        my_destroy(a, p, x);
        throw;}
    return x;}

template <typename A, typename BI, typename U>
BI my_uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
	/* we want to be able to construct ALL or NONE */
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}}
    catch (...) {
        my_destroy(a, p, b);
        throw;}
    return e;}

#endif // Memory_h
