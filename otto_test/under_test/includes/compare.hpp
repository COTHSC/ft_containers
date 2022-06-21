#ifndef COMPARE_HPP
#define COMPARE_HPP

namespace ft {
template <class input_it1, class input_it2>
bool lex_compare(input_it1 first1, input_it1 last1, input_it2 first2,
                 input_it2 last2) {
  input_it1 it1 = first1;
  input_it2 it2 = first2;

  while (it1 != last1) {
    if (it2 == last2 || *it1 > *it2) {
      return false;
    } else if (*it1 < *it2) {
      return true;
    }
    ++it1;
    ++it2;
  }
  return (it2 != last2);
}

template <class input_it1, class input_it2, class compare>
bool lex_compare(input_it1 first1, input_it1 last1, input_it2 first2,
                 input_it2 last2, compare comp) {
  input_it1 it1 = first1;
  input_it2 it2 = first2;

  while (it1 != last1) {
    if (it2 == last2 || comp(*it2, *it1)) {
      return false;
    } else if (comp(*it1, *it2)) {
      return true;
    }
    ++it1;
    ++it2;
  }
  return (it2 != last2);
}

template <class input_it1, class input_it2>
bool equal(input_it1 first1, input_it1 last1, input_it2 first2) {
  while (first1 != last1) {
    if (*first1 != *first2) {
      return false;
      ++first1;
      ++first2;
    }
    return true;
  }
  return true;
}

template <class input_it1, class input_it2, class compare, class comp>
bool equal(input_it1 first1, input_it1 last1, input_it2 first2, comp pred) {
  (void)pred;
  while (first1 != last1) {
    if (*first1 != *first2) {
      return false;
      ++first1;
      ++first2;
    }
    return true;
  }
}

} // namespace ft

#endif
