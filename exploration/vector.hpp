#include <iostream>
#include "vectorIterator.hpp"
#include "is_integral.hpp"
static	class ft_nullptr_t
	{
		private:
			void operator& () const; //no sens to get adress of nullptr

		public:
			template <class T>
				operator T* () const { return 0;}
			template <class C, class T> 
				operator T C::* () const { return 0;}
	} ft_nullptr_t = {};


template<bool Condition, typename T = void>
struct enable_if
{
};
 
template<typename T>
struct enable_if<true, T>
{
    typedef T type;
};

namespace ft {
  
  template<class T, class Allocator = std::allocator<T> > class vector
  {
    public:
    typedef T value_type;
    typedef value_type& reference;
    typedef value_type const & const_reference;
    typedef Allocator allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;

    typedef vectorIterator<T> iterator;
    typedef vectorIterator<const T> const_iterator;
    typedef vectorIterator<T> input_iterator;
    
    /* jconstructors and destructors */

    explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc) {}  ;




    template <class InputIterator>vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _allocator(alloc) {
        assign(first, last);
    };

//  vector() : _size(0), _capacity(0)
//  {
//  };

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

    vector &operator=(const vector& rhs) {
       this->resize(rhs.size());
       for (size_type i = 0; i < this->size(); i++)
           _array[i] = rhs[i];
       return *this;
    }
    ~vector() {
        if (_size)
            _allocator.deallocate(_array, _capacity);
    };

    void clear() {
        while (_size)
            pop_back();
    };
    iterator begin() {
      return iterator(&_array[0]);
    };

    const_iterator begin() const { 
      return const_iterator(&_array[0]); 
    };

    iterator end() {
      return iterator(&_array[_size]);
    };

    const_iterator end() const {
      return const_iterator(&_array[_size]);
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

    void assign (size_type n, const value_type& val) {
        _size = 0;
        while (_size < n) {
            push_back(val);
        }
    };

    template <class InputIterator>
        void    assign(InputIterator first, InputIterator last, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = ft_nullptr_t) {
            _size = 0;
            while (first != last)
            {
                push_back(*first);
                ++first;
            }
        };

    //TODO refactor this, the solution for unnalocated arrays is ugly
    void push_back(const value_type& val) {
      if (_size >= _capacity)
      {
        value_type *tmp;
        if (!_capacity)
        {
            _capacity = 2; 
            _array = _allocator.allocate(_capacity); 
            _allocator.construct(_array + _size, val);
            ++_size;
            return;
        }
        _capacity = _capacity * 2;
        tmp = _allocator.allocate(_capacity); 
        for (size_type i = 0; i < _size ; ++i) {
          _allocator.construct(tmp + i, _array[i]);
        }
        if (_capacity)
            _allocator.deallocate(_array, _capacity);
        _array = tmp;
      }
      _allocator.construct(_array + _size, val);
      ++_size;
    };

    reference at (size_type n) {
        if (n >= _size)
            throw std::out_of_range("exception");
        return (_array[n]);
    };
    const_reference at (size_type n) const {
        if (n >= _size)
            throw std::out_of_range("exception");
        return (_array[n]);
    };
    reference front() {
        return (_array[0]);
    };
    const_reference front() const {
        return (_array[0]);
    };
    reference back() {
        return (_array[_size-1]);
    };
    const_reference back() const
    {
        return (_array[_size-1]);
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
        if (_capacity)
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
    reference operator[](size_type n) { return _array[n]; };
    const_reference operator[] (size_type n) const {return _array[n];};
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
