#include "Vector.hpp"
using namespace ft;

Vector::Vector() : size(0), capacity(5), array(new int[capacity])
{
}

Vector::Vector(const Vector& rhs) : size(rhs.Size()), capacity(rhs.Capacity()), array(new int[capacity])
{
  for (int i; i < rhs.Size(); i++)
  {
    array[i] = rhs.array[i];
  }
}

Vector::Vector(int elements, int value) : size(elements), capacity(elements + 5), array(new int[capacity])
{
  for (int i; i < size; i++)
  {
    array[i] = value;
  }
}

std::ostream& operator<<(std::ostream& ostr, const Vector& rhs)
{
  for (int i = 0; i < rhs.Size(); ++i)
    ostr << rhs.array[i] << std::endl;
  ostr << std::endl << rhs.Capacity() << std::endl;
  return ostr;
}

Vector::~Vector()
{
}

int Vector::Size() const
{
  return size;
}

int Vector::Capacity() const
{
  return capacity;
}

bool Vector::Empty() const
{
  return size == 0;
}

void  Vector::PushBack(int value)
{
  //TODO what if its filled
  array[capacity] = value;
  size++; 
}

bool Vector::operator==(const Vector & rhs) const
{
  if (size != rhs.size)
    return false;
  for (int i = 0; i < size; i++)
  {
    if(array[i] != rhs.array[i])
      return false;
  }
  return true;
}

bool Vector::operator!=(const Vector & rhs) const
{
  return !(*this == rhs);
}
