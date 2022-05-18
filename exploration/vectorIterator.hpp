#include <iostream>
namespace ft {

    struct output_iterator_tag {};
    struct input_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};


    template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
                 struct iterator {
                     typedef T         value_type;
                     typedef Distance  difference_type;
                     typedef Pointer   pointer;
                     typedef Reference reference;
                     typedef Category  iterator_category;
                 };

    template< class Iter >
        struct iterator_traits {
            typedef typename        Iter::difference_type           difference_type;
            typedef typename        Iter::value_type                value_type; 	      
            typedef typename        Iter::pointer                   pointer; 	     
            typedef typename        Iter::reference                 reference; 	     
            typedef typename        Iter::iterator_category         iterator_category;
        };
    template< class T >
        struct iterator_traits<T*> {

            typedef    std::ptrdiff_t                     difference_type;
            typedef    T                                  value_type;	     
            typedef    T*                                 pointer;   
            typedef    T&                                 reference;    
            typedef    ft::random_access_iterator_tag    iterator_category;
        };

    template< class T >
        struct iterator_traits<const T*> {
            typedef    std::ptrdiff_t                     difference_type;
            typedef    T                                  value_type;	     
            typedef    const T*                           pointer;   
            typedef    const T&                           reference;    
            typedef    ft::random_access_iterator_tag    iterator_category;
        };

    template<typename vector> class vectorIterator : public ft::iterator<ft::random_access_iterator_tag, vector>{

    public:
    typedef vector value_type;
    typedef vector& reference_type;
    typedef size_t size_type;
    typedef value_type* pointer_type;
    typedef std::ptrdiff_t difference_type;

    vectorIterator(){};
    vectorIterator(const vectorIterator &rhs) : _ptr(rhs._ptr) {};
//    vectorIterator(pointer_type ptr) : _ptr(ptr) {};
    vectorIterator(pointer_type ptr) : _ptr(ptr) {};
//    vectorIterator(vector *ptr) : _ptr(ptr) {};
    ~vectorIterator(){};

    vectorIterator& operator=(vectorIterator const &rhs) {
      _ptr = rhs._ptr;
      return *this;
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

    vectorIterator& operator+(difference_type idx) { 
      _ptr += idx;
      return *this; 
    };
    
    difference_type operator+(vectorIterator& rhs)  {
       return (_ptr + rhs._ptr); 
    }; 

    difference_type operator-(vectorIterator& rhs)  {
       return (_ptr - rhs._ptr); 
    }; 
    
    vectorIterator& operator-(difference_type diff) {
        _ptr -= diff;
        return (*this); 
    }; 
    vectorIterator &operator+=(difference_type op){_ptr += op; return *this;};
    vectorIterator &operator-=(difference_type op){_ptr -= op; return *this;};

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

    reference_type operator*() {
      return *_ptr;
    };

    private:
    pointer_type _ptr;
  };


  template<typename Iter> class reverse_iterator {


      public:
      typedef           Iter iterator_type;
      typedef typename  ft::iterator_traits<Iter>::iterator_category iterator_category;
      typedef typename	ft::iterator_traits<Iter>::value_type value_type;
      typedef typename  ft::iterator_traits<Iter>::difference_type difference_type;
      typedef typename	ft::iterator_traits<Iter>::pointer pointer;
      typedef typename	ft::iterator_traits<Iter>::reference reference;

      reverse_iterator() : current(iterator_type()) {};
      explicit reverse_iterator (iterator_type it) : current(it) {};
      template <class U>
          reverse_iterator (const reverse_iterator<U>& rev_it) : current(rev_it.base()) {} ;
      iterator_type base() const {
          return current;
      };

      template< class U >
          reverse_iterator& operator=( const reverse_iterator<U>& other ) { 
              current = other.base();
              return *this;
          };

      reference operator*() const {
          Iter tmp = current; 
          return *--tmp;
      };
      pointer operator->() const {
          return &(operator*());
      };
      reference operator[]( difference_type n ) const {
          return (base()[-n-1]);
      };

      reverse_iterator& operator++() {
          --current;
          return *this;
      };

      reverse_iterator operator++( int ) {
          reverse_iterator tmp(base());
          --current;
          return tmp;
      };

      reverse_iterator& operator--() {  
          ++current;
          return *this;
      }
      reverse_iterator operator--( int ) {  
          reverse_iterator tmp(base());
          ++current;
          return tmp;
      };

      reverse_iterator operator+( difference_type n ) const {
        return reverse_iterator(base()-n);
      };

      reverse_iterator operator-( difference_type n ) const {
        return reverse_iterator(base()+n);
      };

      reverse_iterator& operator+=( difference_type n ) {
        current -= n;
        return *this;
      };
      reverse_iterator& operator-=( difference_type n ) {
        current += n;
        return (*this);
      };
      protected: 
        iterator_type current;
  };
template <class Iterator1, class Iterator2>
  bool operator== (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
      return (lhs.base() == rhs.base()); 
  };

template <class Iterator1, class Iterator2>
    bool operator!= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
      return (lhs.base() != rhs.base()); 
    };

template <class Iterator1, class Iterator2>
    bool operator<  (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs){
      return (lhs.base() > rhs.base()); 
    };

template <class Iterator1, class Iterator2>
    bool operator<= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
      return (lhs.base() >= rhs.base()); 
    };

template <class Iterator1, class Iterator2>
    bool operator>  (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs){ 
      return (lhs.base() < rhs.base()); 
    };

template <class Iterator1, class Iterator2>
    bool operator>= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs){
      return (lhs.base() < rhs.base()); 
    };

template< class Iter >
reverse_iterator<Iter>
    operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) {
      return rhs.base() - lhs.base(); 
    };

template< class Iterator >
typename reverse_iterator<Iterator>::difference_type
    operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs );
}
