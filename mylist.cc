template <class T>
struct __list_node {
	typedef void* void_pointerl
	void_pointer prev;
	void_pointer next;
	T data;
};

template <class T, class Ref, class Ptr>
struct __list_iterator {
	typedef __list_iterator<T, Ref, Ptr> self;
	typedef bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef __list_node<T>* link_type;
	link_type node;
	reference operator*() const { return (*node).data; }
	pointer operator->() const { return &(operator*()); }
	self& operator++() {
		node = (link_type)((*node).next);
		return *this;
	}
	self operator++(int) {
		self tmp = *this;
		++*this;
		return tmp;
	}
	self& operator--() {
		node = (link_type)((*node).prev);
		return *this;
	}
	self operator--(int) {
		self tmp = *this;
		--*this;
		return tmp;
	}
};

template <class T, class Alloc = alloc>
class list {
protected:
	typedef __list_node<T> list_node;
public:
	typedef list_node* link_type;
	typedef __list_iterator<T, T&, T*> iterator;
protected:
	link_type node;
};
