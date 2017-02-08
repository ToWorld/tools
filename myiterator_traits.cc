template <class I>
struct iterator_traits {
	typedef typename I::iterator_category 	iterator_category;
	typedef typename I::value_type 			value_type;
	typedef typename I::difference_type		difference_type;
	typedef typename I::pointer				pointer;
	typedef typename I::reference			reference;
};

// partial specifization for regular pointers
template <class T>
struct iterator_traits<T*> {
	typedef random_access_iterator_tag		iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef T*								pointer;
	typedef T&								reference;	
};

// partial specifization for regular const pointers
template <class T>
struct iterator_traits<const T*> {
	typedef random_access_iterator_tag		iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef const T*						pointer;
	typedef const T&						reference;
};
