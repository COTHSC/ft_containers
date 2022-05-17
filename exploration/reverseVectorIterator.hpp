#include <iostream>
#include "vectorIterator.hpp"

namespace ft {

  template<typename vector> class  reverseVectorIterator {

    public:
    typedef vector value_type;
    typedef vector& reference_type;
    typedef size_t size_type;
    typedef value_type* pointer_type;
    typedef std::ptrdiff_t difference_type;

     reverseVectorIterator(){};
     reverseVectorIterator(const reverseVectorIterator &rhs) : _ptr(rhs._ptr) {};
     reverseVectorIterator(const vectorIterator<vector> &rhs) : _ptr(rhs._ptr) {};
//     reverseVectorIterator(pointer_type ptr) : _ptr(ptr) {};
     reverseVectorIterator(pointer_type ptr) : _ptr(ptr) {};
//     reverseVectorIterator(vector *ptr) : _ptr(ptr) {};
    ~reverseVectorIterator(){};

     reverseVectorIterator& operator=(reverseVectorIterator const &rhs) {
     //reverseVectorIterator& operator=(vectorIterator const &rhs) {
      _ptr = rhs._ptr;
      return *this;
    };      

    operator  reverseVectorIterator< const vector>() const;
    bool operator==( reverseVectorIterator const &rhs) {
      return (_ptr == rhs._ptr);
    };      

    bool operator!=( reverseVectorIterator const &rhs) {
      return !(_ptr == rhs._ptr);
    };      

    reference_type operator[](size_type idx) { 
      return *(_ptr + idx);
    };

     reverseVectorIterator& operator+(size_type idx) { 
      _ptr += idx;
      return *this; 
    };
    
    difference_type operator-( reverseVectorIterator& rhs)  {
       return (_ptr - rhs._ptr); 
    }; 
    
     reverseVectorIterator& operator-(difference_type diff) {
        _ptr -= diff;
        return (*this); 
    }; 

     reverseVectorIterator &operator++(void)
    {
      _ptr -= 1;
      return *this;
    };

     reverseVectorIterator operator++(int)
    {
       reverseVectorIterator tmp(*this);
      _ptr -= 1;
      return tmp;
    };

     reverseVectorIterator &operator--(void)
    {
      _ptr += 1;
      return *this;
    };

     reverseVectorIterator operator--(int)
    {
       reverseVectorIterator tmp(*this);
      _ptr += 1;
      return tmp;
    };

    reference_type operator*() {
      return *_ptr;
    };

    pointer_type _ptr;
    private:
  };
}
