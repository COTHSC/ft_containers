#include <iostream>
namespace ft {
template<
    class T,
    class Allocator = std::allocator<T>
> class vector
{
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;

  public:
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
    //TODO this is a print thing meant to be removed
      for (size_type i = 0; i < _size ; ++i) {
        std::cout << _array[i] << " "; 
      }
  };
  vector(const vector& rhs) : _size(rhs.size()), _capacity(rhs.capacity()), _allocator(rhs.get_allocator()), _array(_allocator.allocate(_capacity)) {
      for (size_type i = 0; i < _size ; ++i) {
        _allocator.construct(_array + i, rhs[i]);
      }
    //TODO this is a print thing meant to be removed
      for (size_type i = 0; i < _size ; ++i) {
        std::cout << _array[i] << " "; 
      }
  };

  ~vector() {
    _allocator.deallocate(_array, _capacity);
  };

  size_type size() const {
    return _size;
  };

  bool empty() const {
    return (_size == 0);
  };

  size_type capacity() const {
    return _capacity;
  };

    void push_back(value_type);

    bool operator==(const vector& rhs) const;
    value_type operator[](size_type idx) { return _array[idx]; };
    const value_type operator[](size_type idx) const { return _array[idx]; };
    bool operator!=(const vector& rhs) const;
    friend std::ostream& operator<<(std::ostream& ostr, const vector& rhs);
  
    allocator_type get_allocator() const {
      return _allocator;
    }
  private:
    size_type _size;
    size_type _capacity;
    allocator_type _allocator;
    value_type *_array;
};
};
