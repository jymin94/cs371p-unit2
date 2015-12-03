// Practice writing a custom vector

template<typename T, typename A = std::allocator<T>>
class practice_vector {
	private:
		A _a;
		T* _b;
		T* _e;
	public:
		// default constructor
		explicit practice_vector(int s = 0, const T& v = T(), const A& a = A()) :
   			_a (a),
			_b (s == 0 ? nullptr : _a.allocate(s)),
			_e (s == 0 ? nullptr : _b + s)
		{
			my_unitialized_fill(_a, _b, _e, v);
		}

		//copy constructor l-value
		practice_vector(const practice_vector& rhs) :
   			_a (rhs._a) {
			_b = _a.allocate(rhs.size());
			_e = _b + rhs.size();
			my_unitialized_copy(_a, rhs._b, rhs._e, _b);
		}
		
		//copy constructor r-value
		practice_vector(practice_vector&& rhs) :
   			_a (move(rhs._a)),
			_b (rhs._b),
			_e (rhs._e)	{
			rhs._b = rhs._e = nullptr;
		}

		//assignment operator l-value
		practice_vector& operator = (const practice_vector& rhs) {
			practice_vector new_vector(rhs); //calls copy constructor?!
			std::swap(_b, new_vector._b);
			std::swap(_e, new_vector._e);
			return *this;
		}

		//assignment operator r-value
		practice_vector& operator = (practice_vector&& rhs) {
			my_destroy(_a, _b, _e);
			_a.deallocate(_b, size());

			_b = rhs._b;
			_e = rhs._e;
			rhs._b = nullptr;
			rhs._e = nullptr;
			return *this;
		}

		//destructor
		~practice_vector () {
			my_destroy(_a, _b, _e);
			_a.deallocate(_b, size());
		}
	
		size_type size () const {
			if (_b == nullptr)
				return 0;
			return _e - _b;
		}	

}





// ok try again

template <typename T, typename A = std::allocator<T>>
class p_vector {
	private:
		A _a;
		T* _b;
		T* _e;
	public:
		p_vector(int s = 0, const T& v = T(), const A& a = A()) :
			_a (a),
			/* PLS */
			_b (s == 0 ? nullptr : _a.allocate(s)),
		    _e (s == 0 ? nullptr : _b + s) {
				//fill it
				my_uninitialied_fill(_a, _b, _e, v);
			}	

		p_vector(const p_vector& rhs) :
			/* PLS */
			_a(rhs._a),
			_b(rhs.size() == 0 ? nullptr : _a.allocate(rhs.size())),
			_e(rhs.size() == 0 ? nullptr : _b + rhs.size())
			{
				my_unitialized_copy(_a, rhs._b, rhs._e, _b);
			}

		p_vector(p_vector&& rhs) :
			/* PLS */
			_a(move(rhs._a)),
			_b(rhs._b),
			_e(rhs._e) {
				rhs._b = nullptr;
				rhs._e = nullptr;
		}

		p_vector& operator = (const p_vector& rhs) 
			/* NO */ {
			p_vector that(rhs); //calls copy constructor ok
			std::swap(_b, /* PLS */ that._b);
			std::swap(_e, /* PLS */ that._e);
			return *this;
		}

		p_vector& operator = (p_vector&& rhs) {
			my_destroy(_a, _b, _e);
			_a.deallocate(_b, size());
			
			_b = rhs._b;
			_e = rhs._e;
			rhs._b = nullptr;
			rhs._e = nullptr;
			return *this;
		}

		~p_vector () {
			my_destroy(_a, _b, _e);
			_a.deallocate(_b, size());
		}

		int size() const {
			if (_b == nullptr)
				return 0;
			return _e - _b;
		}

}


// k attempt 3 or something
template <typename T, typename A = std::allocator<T>>
class wut_vector {
	private:
		A _a;
		T* _b;
		T* _e;
	public:
		//default constructor
		wut_vector(int s = 0, const T& v = T(), const A& a = A()) :
			_a(a),
			_b(s == 0 ? nullptr : _a.allocate(s)),
			_e(s == 0 ? nullptr : _b + s) {
			my_unitialized_fill(_a, _b, _e, v);
		}

		//copy constructor, taking in an l-value
		wut_vector(const wut_vector& rhs) :
			_a(rhs._a),
			_b(rhs.size() == 0 ? nullptr : _a.allocate(rhs.size())),
			_e(rhs.size() == 0 ? nullptr : _b + rhs.size()) {
			my_unitialized_copy(_a, rhs._b, rhs._e, _b);
		}

		//copy constructor, taking in an r-value
		/* FUCK FUCK FUCK THIS IS WHERE YOU MOVE!!!!! */
		// BECAUSE YOU TAKE IN A COPY
		wut_vector(wut_vector&& rhs) :
		   _a (move(rhs._a)),
	   	   _b (rhs._b),
		   _e (rhs._e) {
			rhs._b = nullptr;
			rhs._e = nullptr;
		}	   

		//assignment operator, taking in an l-value
		wut_vector& operator = (const wut_vector& rhs) {
			// THIS IS WHERE YOU CALL ON THE COPY CONSTRUCTOR
			// because we need to make a new copy
			wut_vector that(rhs);
			std::swap(_b, that._b);
			std::swap(_e, that._e);
			return *this;
		}

		//assignment operator, taking in an r-value
		wut_vector& operator = (wut_vector&& rhs) {
			my_destroy(_a, _b, _e);
			_a.deallocate(_b, size());

			_b = rhs._b;
			_e = rhs._e;
			rhs._b = nullptr;
			rhs._e = nullptr;
			return *this;
		}

		//destructor
		~wut_vector () {
			my_destroy (_a, _b, _e);
			_a.deallocate(_b, size());
		}
}

/*
 * copy constructor that takes in the && r-value takes in a newly made copy 
 * so you MOVE the allocator to ours and just set its pointers to null
 *
 * assignment operator that takes in the l-value needs to CALL ON THE COPY CONSTRUCTOR
 * AND THEN SWAP!!!!!!
 *
 * assignment operator that takes in the r-value needs to destroy and set to null
 */

//try AGAIN
template <typename T, typename A = std::allocator<T>>
class fuck_vector {
	private:
		A _a;
		T* _b;
		T* _e;
	public:
		fuck_vector(int s = 0, const T& v = T(), const A& a = A()) :
			_a (a),
			_b (s == 0 ? nullptr : _a.allocate(s)),
			_e (s == 0 ? nullptr : _b + s) {
				my_unitialized_fill(_a, _b, _e, v);
		}

		fuck_vector(const fuck_vector& rhs) :
   			_a(rhs._a),
			_b(rhs.size() == 0 ? nullptr : _a.allocate(rhs.size())),
			_e(rhs.size() == 0 ? nullptr : _b + rhs.size())	{
			my_unitialized_copy(_a, rhs._b, rhs._e, _b);
		}

		fuck_vector(fuck_vector&& rhs) :
			_a(move(rhs._a)),
			_b(rhs._b),
			_e(rhs._e) {
			rhs._b = nullptr;
			rhs._e = nullptr;
		}

		fuck_vector& operator = (const fuck_vector& rhs) {
			fuck_vector that(rhs);
			std::swap(_b, that._b);
			std::swap(_e, that._e);
			return *this;
		}

		fuck_vector& operator = (fuck_vector&& rhs) {
			my_destroy(_a, _b, _e);
			_a.deallocate(_b, size());

			_b = rhs._b;
			_e = rhs._e;
			rhs._b = nullptr;
			rhs._e = nullptr;
			return *this;
		}

		~fuck_vector () {
			my_destroy(_a, _b, _e);
			_a.deallocate(_b, size());
		}

		int size() const {
			if (_b == nullptr)
				return 0;
			return _e - _b;
		}
}

// ok just to be sure rly
template <typename T, typename A = std::allocator<T>> 
class shit_vector {
	private:
		A _a;
		T* _b;
		T* _e;
	public:
		explicit shit_vector(int s = 0, const T& v = T(), const A& a = A()) :
			_a (a),
			_b (s == 0 ? nullptr : _a.allocate(s)),
			_e (s == 0 ? nullptr : _b + s) {
			my_unitialized_fill(_a, _b, _e, v);
		}

		shit_vector(const shit_vector& rhs) :
			_a(rhs._a),
			_b(rhs.size() == 0 ? nullptr : _a.allocate(rhs.size())),
			_e(rhs.size() == 0 ? nullptr : _b + rhs.size()) {
				my_unitialized_copy(_a, rhs._b, rhs._e, _b);
		}

		shit_vector (shit_vector&& rhs) :
			_a(move(rhs._a)),
			_b(rhs._b),
			_e(rhs._e) {
				rhs._b = nullptr;
				rhs._e = nullptr;
		}

		shit_vector& operator = (const shit_vector& rhs) {
			shit_vector that(rhs);
			std::swap(_b, that._b);
			std::swap(_e, that._e);
			return *this;
		}

		shit_vector& operator = (shit_vector&& rhs) {
			my_destroy (_a, _b, _e);
			_a.deallocate(_b, size());
			_b = rhs._b;
			_e = rhs._e;
			rhs._b = nullptr;
			rhs._e = nullptr;
			return *this;
		}

		~shit_vector() {
			my_destroy(_a, _b, _e);
			_a.deallocate(_b, size());
		}

		int size() const {
			if (_b == nullptr)
				return 0;
			return _e - _b;
		}
}



