#include "vectorIterator.hpp"


namespace ft {

  template<typename Iter> class reverse_iterator {

      typedef	Iter iterator_type;
      typedef   ft::iterator_traits<Iter>::iterator_category iterator_category;
      typedef	ft::iterator_traits<Iter>::value_type value_type;
      typedef   ft::iterator_traits<Iter>::difference_type difference_type;
      typedef	ft::iterator_traits<Iter>::pointer pointer;
      typedef	ft::iterator_traits<Iter>::reference reference;
}
}


