#include <string>

using namespace std;

class AbstractHuman {
	protected:
		int _age;
		string _name;
	public:
		AbstractHuman(string name, int age = 0) :
		   _name (name),
		   _age (age) {

		}

		virtual int get_age() const = 0;
		virtual string get_name() const = 0;
		virtual char get_gender() const = 0;
		virtual AbstractHuman* clone () const = 0;
};

bool AbstractHuman::equals (const AbstractHuman& rhs) const {
	return _age == rhs._age && _name.equals(rhs._name);
}	

class Woman : AbstractHuman {
	protected:
		char _cup;
		virutal bool equals (const AbstractHuman& rhs) {
			if (const Woman* const p = dynamic_cast<const Woman*>(&rhs))
				return (AbstractHuman::equals(*p) && (_cup == p->_cup));
			return false;
		}	
	public:
		Woman(string name, char cup, int age = 0) :
			AbstractHuman(name, age),
			_cup (cup)	{
		}

		Woman(const Woman&) = default;
		Woman(Woman&&) = default;
		~Woman() = default;
		Woman& operator = (const Woman&) = default;
		Woman& operator = (Woman&&) = default;

		Woman* clone() const {
			return new Woman(*this);
		}

	    const char get_cup () const {
			return _cup;
		}	
		
		const int get_age() const {
			return _age;
		}

		const string get_name() const {
			return _name;
		}

		const char get_gender() const {
			return 'f';
		}
}

class Man : AbstractHuman {
	protected:
		bool _briefs;
		virtual bool equals (const AbstractHuman& rhs) {
			if (const Man* const p = dynamic_cast<const Man*>(&rhs)) {
				return (AbstractHuman::equals(*p) && _briefs == p->_briefs);
			}	
			return false;
		}	
	public:
		Man (string name, bool briefs = false, int age = 0) :
			AbstractHuman(name, age),
			_briefs (briefs)
		{

		}

		Man(const Man&) = default;
		Man(Man&&) = default;
		~Man() = default;
		Man& operator = (const Man&) = default;
		Man& operator = (Man&&) = default;

		const int get_age() const {
			return _age;
		}

		const string get_name() const {
			return _name;
		}

		const bool briefs_or_nah() const {
			return _briefs;
		}

		const char get_gender() const {
			return 'm';
		}

}

template <typename T>
class Handler {
	private:
		friend bool operator == (const Handler& lhs, const Handler& rhs) {
			if (!lhs && !rhs)
				return true;
			if (!lhs || !rhs)
				return false;
			return *lhs._p == *rhs._p;
		}	

		T* _p;

	public:
		Handler(T* p) {
			_p = p;
		}
		
		Handler (const Handler& rhs) {
			if (!rhs._p)
				_p = 0;
			else
				_p = rhs._p->clone();
		}

		Handler& operator = (Handler rhs) {
			swap(rhs);
			//swap(_p, rhs._p);
			return *this;
		}

		void swap (Handler& rhs) {
			std::swap(_p, rhs._p);
		}

		const T& operator * () {
			return *(_p);
		}

		T& operator * () {
			return *_p;
		}

		T* operator -> () {
			return _p;
		}

		const T* operator -> () {
			return _p;
		}

		~Handler () {
			delete _p;
		}
}
