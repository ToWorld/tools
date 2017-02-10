template <class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator {
	typedef random_access_iterator_tag iterator_category;
	typedef T 			value_type;
	typedef Ptr			pointer;
	typedef Ref			reference;
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;
	typedef T**			map_pointer;
	typedef __deque_iterator self;

	T* cur;
	T* first;
	T* last;
	map_pointer node;
};

template <class T, class Alloc=alloc, size_t BufSiz=0>
class deque {
public:
	typedef T value_type;
	typedef __dequeue_iterator<T,T&,T*,BufSiz> iterator;
protected:
	typedef pointer* map_pointer;
protected:
	iterator start;
	iterator finish;
	map_pointer map;
	size_type map_size;
public:
	iterator begin() { return start; }
	iterator end() { return finish; }
	size_type size() const { return finish - start; }
	reference operator[](size_type n) { return start[difference_type(n)]; }
	reference front() { return *start; }
	reference back() { 
		iterator tmp = finish;
		--tmp;
		return *tmp;
	}
	bool empty() const { return finish == start; }
	reference operator*() const { return *cur; }
	pointer operator->() const { return &(operator*()); }
	difference_type operator-(const self& x) const {
		return difference_type(buffer_size())*(node-x.node-1) + (cur-first) + (x.last-x.cur);
	}
	self& operator++() {
		++cur;
		if (cur == last) {
			set_node(node+1);
			cur = first;
		}
		return *this;
	}
	self operator++(int) {
		self tmp = *this;
		++*this;
		return tmp;
	}
	self& operator--() {
		if (cur == first) {
			set_node(node-1);
			cur = last;
		}
		--cur;
		return *this;
	}
	self operator--() {
		self tmp = *this;
		--*this;
		return tmp;
	}
	void set_node(map_pointer new_node) {
		node = new_node;
		first = *new_node;
		last = first + difference_type(buffer_size());
	}
	self operator+(difference_type n) const {
		self tmp = *this;
		return tmp += n;
	}
	self& operator-=(difference_type n) {
		return *this += -n;
	}
	self operator-(difference_type n) const {
		self tmp = *this;
		return tmp -= n;
	}
	reference operator[](difference_type n) const {
		return *(*this+n);
	}
	self& operator+=(difference_type n);
	iterator insert(iterator position, const value_type& x);
	// TODO
};

template <class T, class Alloc, size_t BufSiz>
iterator deque<T,Alloc,BufSiz>::operator+=(difference_type n) {
	difference_type offset = n + (cur-first);
	if (offset >= 0 && offset < difference_type(buffer_size())) {
		cur += n;
	}
	else {
		difference_type node_offset = 
			offset > 0 ? offset / difference_type(buffer_size())
						: -difference_type((-offset-1) / buffer_size()) - 1;
		set_node(node+node_offset);
		cur = first + (offset - node_offset * difference_type(buffer_size()));
	}
	return *this;
}

template <class T, class Alloc, size_t BufSiz>
iterator deque<T,Alloc,BufSiz>::insert(iterator position, const value_type& x) {
	if (position.cur == start.cur) {
		push_front(x);
		return start;
	}
	else if (position.cur == finish.cur) {
		push_back(x);
		iterator tmp = finish;
		--tmp;
		return tmp;
	}
	else {
		return insert_aux(position, x);
	}
}

template <class T, class Alloc, size_t BufSiz>
typename deque<T, Alloc, BufSiz>::iterator
deque<T, Alloc, BufSiz>::insert_aux(iterator pos, const value_type& x) {
	difference_type index = pos - start;
	value_type x_copy = x;
	if (index < size() / 2) {
		push_front(front());
		// TODO
		copy(front2, pos1, front1);
	}
	else {
		push_back(back());
		// TODO
		copy_backward(pos, back2, back1);
	}
	*pos = x_copy;
	return pos;
}
