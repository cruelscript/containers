#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <cassert>

template<class T>
class Vector
{
public:
  using iterator = T*;
  //using const_iterator = const T*;
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  Vector();

  Vector(size_type capacity);

  Vector(const Vector<T>& rhs);

  ~Vector();

  Vector<T>& operator=(const Vector<T>& vector);

  T& operator[](size_type index);

  size_type capacity() const;

  size_type size() const;

  bool isEmpty() const;

  iterator begin();

  iterator end();

  T& front();

  T& back();

  void push_back(const T& value);

  void pop_back();

  void reserve(size_type capacity);

  void clear();

private:
  using byte_type = unsigned char;

  size_type size_;
  size_type capacity_;
  size_type type_size_;
  iterator buffer_;

  void deleteBuffer();
};

template<class T>
Vector<T>::Vector() :
  size_(0),
  capacity_(0),
  type_size_(sizeof(T)),
  buffer_(nullptr)
{}

template<class T>
Vector<T>::Vector(Vector::size_type capacity) :
  size_(0),
  capacity_(capacity),
  type_size_(sizeof(T)),
  buffer_(reinterpret_cast<iterator>(new byte_type[capacity_ * type_size_]))
{}

template<class T>
Vector<T>::Vector(const Vector<T>& rhs) :
  size_(rhs.size_),
  capacity_(rhs.capacity_),
  type_size_(rhs.type_size_),
  buffer_(reinterpret_cast<iterator>(new byte_type[capacity_ * type_size_]))
{
  for(size_type i = 0; i < size_; ++i)
  {
    buffer_[i] = rhs.buffer_[i];
  }
}

template<class T>
Vector<T>::~Vector()
{
  deleteBuffer();
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& vector)
{
  if(&vector == this)
  {
    return *this;
  }
  deleteBuffer();

  size_ = vector.size_;
  capacity_ = vector.capacity_;
  type_size_ = vector.type_size_;
  buffer_ = reinterpret_cast<iterator>(new byte_type[capacity_ * type_size_]);

  for(size_type i = 0; i < size_; ++i)
  {
    buffer_[i] = vector.buffer_[i];
  }
}

template<class T>
T& Vector<T>::operator[](Vector::size_type index)
{
  return buffer_[index];
}

template<class T>
typename Vector<T>::size_type Vector<T>::capacity() const
{
  return capacity_;
}

template<class T>
typename Vector<T>::size_type Vector<T>::size() const
{
  return size_;
}

template<class T>
bool Vector<T>::isEmpty() const
{
  return size_ == 0;
}

template<class T>
typename Vector<T>::iterator Vector<T>::begin()
{
  return buffer_;
}

template<class T>
typename Vector<T>::iterator Vector<T>::end()
{
  return buffer_ + size_;
}

template<class T>
T& Vector<T>::front()
{
  assert(size_ > 0);
  return buffer_[0];
}

template<class T>
T& Vector<T>::back()
{
  assert(size_ > 0);
  return buffer_[size_ - 1];
}

template<class T>
void Vector<T>::push_back(const T& value)
{
  if(size_ >= capacity_)
  {
    if(capacity_ == 0)
    {
      capacity_ = 1;
    }
    reserve(capacity_ * 2);
  }
  new(buffer_ + size_++) T(value);
}

template<class T>
void Vector<T>::pop_back()
{
  buffer_[--size_].~T();
}

template<class T>
void Vector<T>::reserve(Vector::size_type capacity)
{
  capacity_ = capacity;
  iterator newBuffer = reinterpret_cast<iterator>(new byte_type[capacity_ * type_size_]);

  for(size_type i = 0; i < size_; ++i)
  {
    newBuffer[i] = buffer_[i];
  }
  deleteBuffer();
  buffer_ = newBuffer;
}

template<class T>
void Vector<T>::clear()
{
  deleteBuffer();
  size_ = 0;
  capacity_ = 0;
  buffer_(nullptr);
}

template<class T>
void Vector<T>::deleteBuffer()
{
  for(size_type i = 0; i < size_; ++i)
  {
    buffer_[i].~T();
  }
  byte_type* buffer = reinterpret_cast<byte_type*>(buffer_);
  delete[] buffer;
}

#endif
