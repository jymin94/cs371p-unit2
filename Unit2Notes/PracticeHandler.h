#include <string>
//AbstractAnimal class
//Mammal class
//Reptile class
//Handler Animals class
//vector of animals later
using namespace std; 
class AbstractAnimal {
	protected:
		int age;
		int id;
	public:
		AbstractAnimal (int a = 0) :
			age (a) {

		}

		virtual int get_age() const = 0;
		virtual AbstractAnimal* clone() const = 0;
};

bool AbstractAnimal::equals (const AbstractAnimal& rhs) const {
	return age == rhs.age && id == rhs.id;
}

class Mammal : AbstractAnimal {
	protected:
		string fur_count;
		int m_id;
		virtual bool equals (const AbstractAnimal& rhs) const {
			if (const Mammal* const p = dynamic_cast<const Mammal*>(&rhs))
				return AbstractAnimal::equals(*p) && (fur_count == p->fur_count) &&
					(m_id == p->m_id);
			return false;
		}

		virtual bool equals (const AbstactAnimals& rhs) const {
			if (const Mammal* const p = dynamic_cast<const Mammal*>(&rhs))
				return AbstractAnimal::equals(*p) && (fur_count == p->fur_count) && (m_id == p->m_id);
			return false;
		}
	public:
		Mammal(string f, int a = 0) :
			AbstractAnimal(a),
			fur_count(f) {

		}	

		virtual Mammal* clone () const {
			return new Mammal(*this);
		}

		int get_age() const {
			return age;
		}

		int get_id() const {
			return m_id;
		}
};


class Reptile : AbstractAnimal {
	protected:
		double blood_temp;
		int r_id;

		virtual bool equals (const AbstractAnimal& rhs) const {
			if (const Reptile* const p = dynamic_cast<const Reptile*>(&rhs))
				return AbstractAnimal::equals(*p) && (blood_temp == p->blood_temp) 
					&& (r_id == p->r_id);
			return false;
		}
	public:
		Reptile (double b_t = 0.0, int id = 0, int a = 0) :
			AbstractAnimal(a),
			blood_temp(b_t),
			r_id(id) {

		}

		virtual Reptile* clone() const {
			return new Reptile(*this);
		}

		int get_age () const {
			return age;
		}

		int get_id() const {
			return r_id;
		}
}

template <typename T>
class AnimalHandler  {
	private;

		friend bool operator == (const AnimalHandler& lhs, const AnimalHandler& rhs) {
			if (!lhs._p && !rhs._p)
				return true;
			if (!lhs._p || !rhs._p)
				return false;
			return (*lhs._p == *rhs._p);

		}
		T* _p;

	public:
		AnimalHandler(T* p) {
			_p = p;
		}

		AnimalHandler (const AnimalHandler& rhs) {
			if (!rhs._p)
				_p = nullptr;
			else
				_p = rhs._p->clone(); // OK OK OK OK
		}

		AnimalHandler& operator = (AnimalHandler rhs) {
			swap(rhs);
			return *this;
		}

		void swap (AnimalHandler& rhs) {
			std::swap(_p, rhs._p); // FUCK
		}

		~AnimalHandler() {
			delete _p;
		}

		T& operator * () {
			return *_p;
		}

		const T& operator * () {
			return *_p;
		}

		T* operator -> () {
			return _p;
		}

		const T* operator -> () {
			return _p;
		}
		
}

//VECTOR OF HUMANS
vector<Handler<AbstractHuman>> x (10);

//VECTOR OF WOMEN
vector<Handler<AbstractHuman>> y (10, new Woman(...));
