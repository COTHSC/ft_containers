#include "Vector2.hpp"

int main()
{
  ft::vector<int> test(5, 0);
  ft::vector<std::string> testStr(5, "wow");
  ft::vector<std::string> testCpy(testStr);

  std::cout << testStr << std::endl;
  testStr.push_back("not so wow");
  testStr.push_back("not so wow");
  testStr.push_back("not so wow");
  testStr.push_back("not so wow");
  testStr.push_back("not so wow");
  testStr.push_back("not so wow");
  testStr.push_back("not so wow");

  std::cout << testStr << std::endl;
  
  std::cout << "test empty function, should return false: " << testStr.empty() << std::endl;

  testStr.pop_back(); 
  testStr.pop_back(); 
  testStr.pop_back(); 
  testStr.pop_back(); 
  testStr.pop_back(); 
  
  std::cout << testStr << std::endl;
  
  testStr.pop_back(); 
  testStr.pop_back(); 
  testStr.pop_back(); 
  testStr.pop_back(); 
  testStr.pop_back(); 
  testStr.pop_back(); 
  testStr.pop_back(); 
  testStr.pop_back(); 
  testStr.pop_back(); 
  
  std::cout << "test empty function, should return true: " << testStr.empty() << std::endl;
  testStr.push_back("not so wow");
  testStr.push_back("not so wow");
  testStr.push_back("not so wow");
  std::cout << "this tests size(), capacity() and max_size()" << std::endl;
  std::cout << testStr.size() << std::endl;
  std::cout << testStr.capacity() << std::endl;
  std::cout << testStr.max_size() << std::endl;


  std::cout << "this tests size(), capacity() and max_size()" << std::endl;
  std::cout << testStr.capacity() << std::endl;
  testStr.reserve(21);
  std::cout << testStr.capacity() << std::endl;
  testStr.reserve(21);
  std::cout << testStr.capacity() << std::endl;

  return 0;
}
