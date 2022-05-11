//its a good thing to learn how to type properly isnt it?
#include <iostream>
namespace ft {
class Vector 
{
  public:
    Vector();
    ~Vector();
    Vector(const Vector& rhs);
    Vector(int elements, int value = 0);
    

    void PushBack(int);
    int Size() const;
    bool Empty() const;
    int Capacity() const;

    bool operator==(const Vector& rhs) const;
    bool operator!=(const Vector& rhs) const;
    friend std::ostream& operator<<(std::ostream& ostr, const Vector& rhs);
  private:
    int size;
    int capacity;
    int *array;
};

}
