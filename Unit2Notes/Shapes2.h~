// ---------
// Shapes2.h
// ---------

#ifndef Shapes2_h
#define Shapes2_h

#include <utility> // !=

using std::rel_ops::operator!=;

class Circle : public Shape {
    private:
        int _r;

    protected:
        virtual bool equals (const Shape& rhs) const {
            if (const Circle* const p = dynamic_cast<const Circle*>(&rhs))
                return Shape::equals(*p) && (_r == p->_r);
            return false;}

        virtual std::istream& read (std::istream& in) {
            return Shape::read(in) >> _r;}

        virtual std::ostream& write (std::ostream& out) const {
            return Shape::write(out) << " " << _r;}

    public:
        Circle (int x, int y, int r) :
                Shape (x, y),
                _r    (r)
            {}

        Circle             (const Circle&)  = default;
        Circle             (      Circle&&) = default;
        ~Circle            ()               = default;
        Circle& operator = (const Circle&)  = default;
        Circle& operator = (      Circle&&) = default;

        virtual double area () const {
            return 3.14 * _r * _r;}

        int radius () const {
            return _r;}};

#endif // Shapes2_h
