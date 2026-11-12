#include "ints.hpp"
#include <utility>
#include <limits>
#include <stdexcept>
#include <cstddef>

Ints::Ints():
  capacity_(0),
  size_(0),
  data_(nullptr)
{}

Ints::Ints(size_t size, int value):
  capacity_(size),
  size_(size),
  data_(new int[size])
{
  for (size_t i = 0; i < size_; ++i)
  {
    data_[i] = value;
  }
}

Ints::Ints(const Ints & rhs): //копирование
  capacity_(rhs.capacity_),
  size_(rhs.size_),
  data_(new int[rhs.capacity_])
{
  for (size_t i = 0; i < size_; ++i)
  {
    data_[i] = rhs.data_[i];
  }
}

Ints::Ints(Ints && rhs) noexcept: //перемещение
  capacity_(rhs.capacity_),
  size_(rhs.size_),
  data_(rhs.data_)
{
  rhs.capacity_ = 0;
  rhs.size_ = 0;
  rhs.data_ = nullptr;
}

Ints & Ints::operator=(const Ints & rhs) //1
{
  if (this != &rhs)
  {
    Ints temp(rhs);
    
    std::swap(capacity_, temp.capacity_);
    std::swap(size_, temp.size_);
    std::swap(data_, temp.data_);
  }

  return *this;
}

Ints & Ints::operator=(Ints && rhs) noexcept //2
{
  if (this != &rhs)
  {
    delete[] data_;
    
    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    data_ = rhs.data_;
    
    rhs.capacity_ = 0;
    rhs.size_ = 0;
    rhs.data_ = nullptr;
  }

  return *this;
}

Ints::~Ints() //деструктор
{
  delete[] data_;
}

Ints Ints::operator+(const Ints & rhs) const 
{
  if (size_ != rhs.size_)
  {
    throw std::invalid_argument("Different sizes");
  }

  Ints result(size_, 0);

  for (size_t i = 0; i < size_; ++i)
  {
    long long sum = static_cast<long long>(data_[i]) + rhs.data_[i];

    if (sum > std::numeric_limits<int>::max() || sum < std::numeric_limits<int>::min())
    {
      throw std::overflow_error("Overflow");
    }

    result.data_[i] = static_cast<int>(sum);
  }

  return result;
}

size_t Ints::getSize() const noexcept
{
  return size_;
}

void Ints::set(size_t id, int i) noexcept
{
  data_[id] = i;
}

int Ints::get(size_t id) const noexcept
{
  return data_[id];
}

void Ints::setSafe(size_t id, int i)
{
  if (id >= size_)
  {
    throw std::out_of_range("Invalid id");
  }

  set(id, i);
}

int Ints::getSafe(size_t id) const
{
  if (id >= size_)
  {
  throw std::out_of_range("Invalid id");
  }

  return get(id);
}

Ints Ints::append(int i)
{
  Ints result(*this);

  if (result.size_ >= result.capacity_)
  {
    result.resize();
  }

  result.data_[result.size_] = i;
  ++result.size_;

  return result;
}

void Ints::resize()
{
  size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
  int * new_data = new int[new_cap];

  for (size_t i = 0; i < size_; ++i)
  {
    new_data[i] = data_[i];
  }

  delete[] data_;
  
  data_ = new_data;
  capacity_ = new_cap;
}
