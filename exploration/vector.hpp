#include <iostream>

namespace ft {
  
  template<typename Vector> class constVectorIterator {

    typedef Vector value_type;
    typedef value_type* pointer_type;

    public:
      constVectorIterator(){};
      constVectorIterator(const constVectorIterator &rhs) : _ptr(rhs._ptr) {};
      constVectorIterator(pointer_type ptr) : _ptr(ptr) {};
      ~constVectorIterator(){};

      constVectorIterator& operator=(constVectorIterator const &rhs) {
        _ptr = rhs._ptr;
      };      

      bool operator==(constVectorIterator const &rhs) {
        return (_ptr == rhs._ptr);
      };      

      bool operator!=(constVectorIterator const &rhs) {
        return !(_ptr == rhs._ptr);
      };      

	constVectorIterator &operator++(void)
	{
		_ptr += 1;
		return *this;
	};

	constVectorIterator operator++(int)
	{
		constVectorIterator tmp(*this);
		_ptr += 1;
		return tmp;
	};

	constVectorIterator &operator--(void)
	{
		_ptr -= 1;
		return *this;
	};

	constVectorIterator operator--(int)
	{
		constVectorIterator tmp(*this);
		_ptr -= 1;
		return tmp;
	};

    value_type operator*() {
        return *_ptr;
    };

    private:
      pointer_type _ptr;
  };

  template<typename Vector> class vectorIterator {

    typedef Vector value_type;
    typedef size_t size_type;
    typedef value_type* pointer_type;
    typedef std::ptrdiff_t							difference_type;
    public:
      vectorIterator(){};
      vectorIterator(const vectorIterator &rhs) : _ptr(rhs._ptr) {};
      vectorIterator(pointer_type ptr) : _ptr(ptr) {};
      ~vectorIterator(){};

      vectorIterator& operator=(vectorIterator const &rhs) {
        _ptr = rhs._ptr;
      };      

      bool operator==(vectorIterator const &rhs) {
        return (_ptr == rhs._ptr);
      };      

      bool operator!=(vectorIterator const &rhs) {
        return !(_ptr == rhs._ptr);
      };      

    difference_type operator[](size_type idx) { 
        return _ptr[idx];
         
    };

	vectorIterator &operator++(void)
	{
		_ptr += 1;
		return *this;
	};

	vectorIterator operator++(int)
	{
		vectorIterator tmp(*this);
		_ptr += 1;
		return tmp;
	};

	vectorIterator &operator--(void)
	{
		_ptr -= 1;
		return *this;
	};

	vectorIterator operator--(int)
	{
		vectorIterator tmp(*this);
		_ptr -= 1;
		return tmp;
	};

    value_type operator*() {
        return *_ptr;
    };

    private:
      pointer_type _ptr;
  };

  template<class T, class Allocator = std::allocator<T> > class vector
  {
    public:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;

    typedef vectorIterator<T> iterator;
    typedef constVectorIterator<const T> const_iterator;
    vector() : _size(0), _capacity(0)
    {
    };

    explicit vector(const Allocator& alloc ) : _size(0), _capacity(0), _allocator(alloc) 
    {
    };

    explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : _size(count), _capacity(_size *2), _allocator(alloc), _array(_allocator.allocate(_capacity)) {
      for (size_type i = 0; i < _size ; ++i) {
        _allocator.construct(_array + i, value);
      }
    };

    vector(const vector& rhs) : _size(rhs.size()), _capacity(rhs.capacity()), _allocator(rhs.get_allocator()), _array(_allocator.allocate(_capacity)) {
      for (size_type i = 0; i < _size ; ++i) {
        _allocator.construct(_array + i, rhs[i]);
      }
    };

    ~vector() {
      _allocator.deallocate(_array, _capacity);
    };

    iterator begin() {
      return iterator(_array);
    };

    const_iterator begin() const {
      return const_iterator(_array);
    };

    const_iterator end() const {
      return const_iterator(_array + _size);
    };

    iterator end() {
      return iterator(_array + _size);
    };

    size_type size() const {
      return _size;
    };

    size_type max_size() const {
      return _allocator.max_size();
    }

    bool empty() const {
      return (_size == 0);
    };

    size_type capacity() const {
      return _capacity;
    };
    //iterator insert (iterator position, const value_type& val);
    //void insert() {};
    void push_back(const value_type& val) {
      if (_size == _capacity)
      {
        value_type *tmp;
        _capacity = _capacity * 2;
        tmp = _allocator.allocate(_capacity); 
        for (size_type i = 0; i < _size ; ++i) {
          _allocator.construct(tmp + i, _array[i]);
        }
        _allocator.deallocate(_array, _capacity);
        _array = tmp;
      }
      _allocator.construct(_array + _size, val);
      ++_size;
    };

    void reserve (size_type n) {
      if (n > _capacity)
      {
        value_type *tmp;
        _capacity = _capacity * 2;
        tmp = _allocator.allocate(_capacity); 
        for (size_type i = 0; i < _size ; ++i) {
          _allocator.construct(tmp + i, _array[i]);
        }
        _allocator.deallocate(_array, _capacity);
        _array = tmp;
      }
    };

    void resize (size_type n, value_type val = value_type()) {
      while (n < _size)
        pop_back();
      while (n > _size)
        push_back(val);
    };

    void pop_back() {
      if (_size > 0)
        _allocator.destroy(_array + --_size);
    };

    friend std::ostream& operator<<(std::ostream& ostr, const vector& rhs)
    {
      for (size_type i = 0; i < rhs.size(); ++i)
        ostr << rhs[i] << std::endl;
      ostr << "THE CAPACITY OF THIS ARRAY IS: " << rhs.capacity() << std::endl;
      return ostr;
    };

    bool operator==(const vector& rhs) const;
    value_type operator[](size_type idx) { return _array[idx]; };
    const value_type operator[](size_type idx) const { return _array[idx]; };
    bool operator!=(const vector& rhs) const;

    allocator_type get_allocator() const {
      return _allocator;
    }
    
    private:
    size_type _size;
    size_type _capacity;
    allocator_type _allocator;
    value_type *_array;

    void _offset_by_n(size_type n, size_type start_point) {
      if (_size + n >= _capacity)
      {
        value_type *tmp;
        _capacity = _capacity * 2;
        tmp = _allocator.allocate(_capacity); 
        for (size_type i = 0; i < _size ; ++i) {
          _allocator.construct(tmp + i, _array[i]);
        }
        _allocator.deallocate(_array, _capacity);
        _array = tmp;
        _offset_by_n(n);
      }
      size_type i = _size;
      while (i >= start_point)
        _array[--i + n] = _array[i];
    };
  };
};
