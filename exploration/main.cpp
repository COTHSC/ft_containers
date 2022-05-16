#include "vector.hpp"

void print(ft::vector<int> const &vct)
{

  //  (void)vct;
    ft::vector<int>::const_iterator it = vct.begin();
}

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

  std::cout << testStr << std::endl;
  std::cout << testStr.size() << std::endl;
  testStr.resize(2);
  std::cout << testStr.size() << std::endl;
  std::cout << testStr << std::endl;
  testStr.resize(10);
  std::cout << testStr.size() << std::endl;
  std::cout << testStr << std::endl;


  ft::vector<int>::iterator It = test.begin();
  ft::vector<int>::iterator constIt = test.begin();
  It[2] = 1;
  while (It != test.end())
  {
      std::cout << *It << std::endl;
      std::cout << It[0] << std::endl;
      
      It++;
  }
  return 0;
}
