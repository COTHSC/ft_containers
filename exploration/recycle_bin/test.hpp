#include <iostream>
template<typename blDataType>
class blRawIterator
{
public:

    using iterator_category = std::random_access_iterator_tag;
    using value_type = blDataType;
    using difference_type = std::ptrdiff_t;
    using pointer = blDataType*;
    using reference = blDataType&;

public:

    blRawIterator(blDataType* ptr = nullptr){m_ptr = ptr;}
    blRawIterator(const blRawIterator<blDataType>& rawIterator) = default;
    ~blRawIterator(){}

    blRawIterator<blDataType>&                  operator=(const blRawIterator<blDataType>& rawIterator) = default;
    blRawIterator<blDataType>&                  operator=(blDataType* ptr){m_ptr = ptr;return (*this);}

    operator                                    bool()const
    {
        if(m_ptr)
            return true;
        else
            return false;
    }

    bool                                        operator==(const blRawIterator<blDataType>& rawIterator)const{return (m_ptr == rawIterator.getConstPtr());}
    bool                                        operator!=(const blRawIterator<blDataType>& rawIterator)const{return (m_ptr != rawIterator.getConstPtr());}

    blRawIterator<blDataType>&                  operator+=(const difference_type& movement){m_ptr += movement;return (*this);}
    blRawIterator<blDataType>&                  operator-=(const difference_type& movement){m_ptr -= movement;return (*this);}
    blRawIterator<blDataType>&                  operator++(){++m_ptr;return (*this);}
    blRawIterator<blDataType>&                  operator--(){--m_ptr;return (*this);}
    blRawIterator<blDataType>                   operator++(int){auto temp(*this);++m_ptr;return temp;}
    blRawIterator<blDataType>                   operator--(int){auto temp(*this);--m_ptr;return temp;}
    blRawIterator<blDataType>                   operator+(const difference_type& movement){auto oldPtr = m_ptr;m_ptr+=movement;auto temp(*this);m_ptr = oldPtr;return temp;}
    blRawIterator<blDataType>                   operator-(const difference_type& movement){auto oldPtr = m_ptr;m_ptr-=movement;auto temp(*this);m_ptr = oldPtr;return temp;}

    difference_type                             operator-(const blRawIterator<blDataType>& rawIterator){return std::distance(rawIterator.getPtr(),this->getPtr());}

    blDataType&                                 operator*(){return *m_ptr;}
    const blDataType&                           operator*()const{return *m_ptr;}
    blDataType*                                 operator->(){return m_ptr;}

    blDataType*                                 getPtr()const{return m_ptr;}
    const blDataType*                           getConstPtr()const{return m_ptr;}

protected:

    blDataType*                                 m_ptr;
};


template<typename blDataType>
class blCustomContainer
{
public: // The typedefs

    typedef blRawIterator<blDataType>              iterator;
    typedef blRawIterator<const blDataType>        const_iterator;

    typedef blRawReverseIterator<blDataType>       reverse_iterator;
    typedef blRawReverseIterator<const blDataType> const_reverse_iterator;

                            .
                            .
                            .

public:  // The begin/end functions

    iterator                                       begin(){return iterator(&m_data[0]);}
    iterator                                       end(){return iterator(&m_data[m_size]);}

    const_iterator                                 cbegin(){return const_iterator(&m_data[0]);}
    const_iterator                                 cend(){return const_iterator(&m_data[m_size]);}

    reverse_iterator                               rbegin(){return reverse_iterator(&m_data[m_size - 1]);}
    reverse_iterator                               rend(){return reverse_iterator(&m_data[-1]);}

    const_reverse_iterator                         crbegin(){return const_reverse_iterator(&m_data[m_size - 1]);}
    const_reverse_iterator                         crend(){return const_reverse_iterator(&m_data[-1]);}

                            .
                            .
                            .
    // This is the pointer to the
    // beginning of the data
    // This allows the container
    // to either "view" data owned
    // by other containers or to
    // own its own data
    // You would implement a "create"
    // method for owning the data
    // and a "wrap" method for viewing
    // data owned by other containers

    blDataType*                                    m_data;
};
