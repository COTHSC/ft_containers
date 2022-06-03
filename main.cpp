#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"

void print(ft::vector<int> const &vct) {
  ft::vector<int>::const_iterator it = vct.begin();
}

int main() {
  ft::map<int, std::string> newmap;

  newmap.insert(ft::make_pair(1, "one"));
  newmap._red_black_tree.printBT();
  newmap.insert(ft::make_pair(2, "two"));
  // newmap.insert(ft::make_pair(2, "one"));
  newmap.insert(ft::make_pair(3, "three"));
  newmap.insert(ft::make_pair(4, "four"));
  newmap.insert(ft::make_pair(5, "five"));
  newmap.insert(ft::make_pair(7, "seven"));
  newmap.insert(ft::make_pair(6, "six"));
  newmap.insert(ft::make_pair(8, "eight"));
  newmap.insert(ft::make_pair(9, "nine"));
  newmap.insert(ft::make_pair(10, "ten"));
  ft::map<int, std::string>::iterator it = newmap.begin();
  std::cerr << (*it).second << std::endl;

  newmap._red_black_tree.printBT();
  // ft::map<int, std::string>::iterator it = newmap.begin();
  // ft::vector<int> test(5, 0);
  // ft::vector<std::string> testStr(5, "wow");
  // ft::vector<std::string> testCpy(testStr);

  // std::cout << testStr << std::endl;
  // testStr.push_back("not so wow");
  // testStr.push_back("not so wow");
  // testStr.push_back("not so wow");
  // testStr.push_back("not so wow");
  // testStr.push_back("not so wow");
  // testStr.push_back("not so wow");
  // testStr.push_back("not so wow");

  // std::cout << testStr << std::endl;
  //
  // std::cout << "test empty function, should return false: " <<
  // testStr.empty() << std::endl;

  // testStr.pop_back();
  // testStr.pop_back();
  // testStr.pop_back();
  // testStr.pop_back();
  // testStr.pop_back();
  //
  // std::cout << testStr << std::endl;
  //
  // testStr.pop_back();
  // testStr.pop_back();
  // testStr.pop_back();
  // testStr.pop_back();
  // testStr.pop_back();
  // testStr.pop_back();
  // testStr.pop_back();
  // testStr.pop_back();
  // testStr.pop_back();
  //
  // std::cout << "test empty function, should return true: " << testStr.empty()
  // << std::endl; testStr.push_back("not so wow"); testStr.push_back("not so
  // wow"); testStr.push_back("not so wow"); std::cout << "this tests size(),
  // capacity() and max_size()" << std::endl; std::cout << testStr.size() <<
  // std::endl; std::cout << testStr.capacity() << std::endl; std::cout <<
  // testStr.max_size() << std::endl;

  // std::cout << "this tests size(), capacity() and max_size()" << std::endl;
  // std::cout << testStr.capacity() << std::endl;
  // testStr.reserve(21);
  // std::cout << testStr.capacity() << std::endl;
  // testStr.reserve(21);
  // std::cout << testStr.capacity() << std::endl;

  // std::cout << testStr << std::endl;
  // std::cout << testStr.size() << std::endl;
  // testStr.resize(2);
  // std::cout << testStr.size() << std::endl;
  // std::cout << testStr << std::endl;
  // testStr.resize(10);
  // testStr.resize(5);
  // std::cout << testStr.size() << std::endl;
  // std::cout << testStr << std::endl;

  // ft::vector<int>::iterator It = test.begin();
  // ft::vector<int>::iterator constIt = test.begin();
  // It[2] = 1;
  // while (It != test.end())
  //{
  //     std::cout << *It << std::endl;
  //     std::cout << It[0] << std::endl;
  //     *It = 1;
  //     It++;
  // }
  //
  // ft::vector<std::string>::iterator first = testStr.begin();
  // ft::vector<std::string>::iterator last = testStr.begin() + 2;
  // testCpy.assign(first, last);
  // // test.assign(2, 7);
  // //
  // ft::vector<std::string> ts(5, "waw");
  // // std::cout << ts << std::endl;
  // ft::vector<std::string>::iterator it = ts.begin();
  // //*it = "wow";
  // //
  // // ft::vector<std::string>::reverse_iterator rit = ts.rbegin();
  // while (rit != ts.rend())
  //{
  //    std::cout << *rit << std::endl;
  //    //++rit;
  //    //--rit;
  //    rit = rit + 1;
  //}
  // ts.insert(it, "wow1");
  // std::cout << ts << std::endl;
  // it = ts.begin();
  // ts.insert(it, "wow2");
  // it = ts.begin();
  // std::cout << ts << std::endl;
  // ts.insert(it, "wow3");
  // it = ts.begin();
  // std::cout << ts << std::endl;
  // ts.insert(it, "wow4");
  // it = ts.begin();
  // std::cout << ts << std::endl;
  // ts.insert(it, "wow4");
  // it = ts.begin();

  // std::cout << ts << std::endl;
  // it = ts.end();
  // ts.insert(it, "wow4");
  // it = ts.end();
  // ts.insert(it, "wow4");
  // it = ts.end();
  // ts.insert(it, "wow4");
  // it = ts.end();
  // ts.insert(it, "wow4");
  // it = ts.end();
  // ts.insert(it, "wow4");
  // it = ts.end();
  // ts.insert(it, "wow4");
  // it = ts.end();
  // ts.insert(it, "wow4");
  // it = ts.end();
  // ts.insert(it, "wow4");
  // it = ts.end();
  // ts.insert(it, "wow4");
  // it = ts.end();
  // ts.insert(it, "wow4");
  // it = ts.end();
  // ts.insert(it, "wow4");
  // it = ts.end();
  // ts.insert(it, "wow4");
  // std::cout << ts << std::endl;
  // it = ts.begin();
  // ts.insert(it, "wow4");
  // it = ts.begin();
  // ts.insert(it, "wow4");
  // it = ts.begin();
  // ts.insert(it, "wow4");
  // it = ts.begin();
  // ts.insert(it, "wow4");
  // it = ts.begin();
  // ts.insert(it, "wow4");
  // it = ts.begin();
  // ts.insert(it, "wow4");
  // it = ts.begin();
  // ts.insert(it, "wow4");
  // it = ts.begin();
  // ts.insert(it, "wow4");
  // it = ts.begin();
  // ts.insert(it, "wow4");
  // it = ts.begin();
  // ts.insert(it, "wow4");
  // it = ts.begin();
  // ts.insert(it, 15, "inserted by range");
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // it = ts.begin();
  // ts.erase(it);
  // std::cout << ts << std::endl;

  return 0;
}
