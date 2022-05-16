#include <iostream>
namespace ft {

  template<typename vector> class vectorIterator {

    typedef vector value_type;
    typedef vector& reference_type;
    typedef size_t size_type;
    typedef value_type* pointer_type;
    typedef std::ptrdiff_t							difference_type;

    public:
    vectorIterator(){};
    vectorIterator(const vectorIterator &rhs) : _ptr(rhs._ptr) {};
//    vectorIterator(pointer_type ptr) : _ptr(ptr) {};
    vectorIterator(pointer_type ptr) : _ptr(ptr) {};
//    vectorIterator(vector *ptr) : _ptr(ptr) {};
    ~vectorIterator(){};

    vectorIterator& operator=(vectorIterator const &rhs) {
      _ptr = rhs._ptr;
    };      

    operator vectorIterator< const vector>() const;
    bool operator==(vectorIterator const &rhs) {
      return (_ptr == rhs._ptr);
    };      

    bool operator!=(vectorIterator const &rhs) {
      return !(_ptr == rhs._ptr);
    };      

    reference_type operator[](size_type idx) { 
      return *(_ptr + idx);
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

}
