template <class T, class Alloc = alloc>
class vector {
public:
	typedef T 		value_type;
	typedef value_type* 	iterator;
	typedef value_type&	reference;
	typedef size_t 		size_type;
protected:
	iterator	start;
	iterator	finish;
	iterator	end_of_storage;
public:
	iterator begin() { return start; }
	iterator end() { return finish; }
	size_type size() const {
		return size_type(end() - begin());
	}
	size_type capacity() const {
		return size_type(end_of_storage - begin());
	}
	bool empty() const {
		return begin() == end();
	}
	reference operator[](size_type n) {
		return *(begin()+n);
	}
	refernece front() {
		return *begin();
	}
	reference back() {
		return *(end()-1)
	}
	void push_back(const T& x);
};

template <class T, class Alloc>
void vector<T,Alloc>::insert_aux(iterator position, const T& x) {
	if (finish != end_of_storage) {
		construct(finish, *(finish - 1));
		++finish;
		T x_copy = x;
		copy_backward(position, finish - 2, finish - 1);
		*position = x_copy;
	}
	else {
		const size_type old_size = size();
		const size_type len = old_size != 0 ? 2 * old_size : 1;
		
		iterator new_start = data_allocator::allocate(len);
		iterator new_finish = new_start;
		try {
			// copy from src to dst
			new_finish = uninitialized_copy(start, position, new_start);
			construct(new_finish, x);	assign new value for x
			++new_finish;
			new_finish = uinitialized_copy(position, finish, new_finish);
		}
		catch(...) {
			// "commit or rollback" semantics.
			destroy(new_start, new_finish);
			data_allocator::deallocate(new_start, len);
			throw;
		}
		destroy(begin(), end());
		deallocate();
		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + len;
	}
}

template <class T, class Alloc>
void vector<T,Alloc>::push_back(const T& x) {
	if (finish != end_of_storage) {
		construct(finish, x);
		++finish;
	}
	else {
		insert_aux(end(), x);	
	}
}
