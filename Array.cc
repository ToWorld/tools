template <typename _Tp, std::size_t _Nm>
struct array {
	typedef _Tp 		value_type;
	typedef _Tp*		pointer;
	typedef value_type*	iterator;
	
	// Support for zero-sized arrays mandatory.
	value_type _M_instance[_Nm ? _Nm : 1];

	iterator begin() {
		return iterator(&_M_instance[0]);	
	}
	iterator end() {
		return iterator(&_M_instance[_Nm]);
	}
};
