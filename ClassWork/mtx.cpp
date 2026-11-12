#include "mtx.hpp"
#include <limits>
#include <stdexcept>
#include <utility>
#include <cstddef>

Mtx::Mtx():
  m(0),
  n(0),
  data()
{}

Mtx::Mtx(size_t m, size_t n):
  m(m),
  n(n),
  data(m * n, 0)
{
  if (m > 0 && n > std::numeric_limits<size_t>::max() / m)
  {
    throw std::overflow_error("Overflow in matrix size");
  }
}

Mtx Mtx::sum(const Mtx & oth) const
{
  if (m != oth.m || n != oth.n)
  {
    throw std::invalid_argument("Matrix sizes do not match");
  }

  Mtx res(m, n);
  for (size_t i = 0; i < data.getSize(); ++i)
  {
    long long s = static_cast<long long>(data.get(i)) + oth.data.get(i);
    if (s > std::numeric_limits<int>::max() || s < std::numeric_limits<int>::min())
    {
      throw std::overflow_error("Overflow in sum");
    }
    res.data.set(i, static_cast<int>(s));
  }
  return res;
}

Mtx Mtx::mul(const Mtx & oth) const
{
  if (n != oth.m)
  {
    throw std::invalid_argument("Matrix dimensions are incompatible");
  }

  Mtx res(m, oth.n);
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < oth.n; ++j)
    {
      long long sm = 0;
      for (size_t k = 0; k < n; ++k)
      {
        sm += static_cast<long long>(data.get(i * n + k)) * oth.data.get(k * oth.n + j);
        if (sm > std::numeric_limits<int>::max() || sm < std::numeric_limits<int>::min())
        {
          throw std::overflow_error("Overflow in mul");
        }
      }
      res.data.set(i * oth.n + j, static_cast<int>(sm));
    }
  }
  return res;
}

Mtx Mtx::transpose() const
{
  Mtx res(n, m);
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      res.data.set(j * m + i, data.get(i * n + j));
    }
  }
  return res;
}

int Mtx::det() const
{
  if (m != n)
  {
    throw std::invalid_argument("Matrix must be square");
  }

  if (m == 1) return data.get(0);
  if (m == 0) return 0;

  if (m == 2)
  {
    return data.get(0) * data.get(3) - data.get(1) * data.get(2);
  }
  
  throw std::logic_error("det() not implemented for size > 2");
}

Mtx Mtx::add_row(int init) const
{
  Mtx res(m + 1, n);
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      res.data.set(i * n + j, data.get(i * n + j));
    }
  }
  for (size_t j = 0; j < n; ++j)
  {
    res.data.set(m * n + j, init);
  }
  return res;
}

Ints Mtx::getCol(size_t id) const
{
  Ints res(m, 0);
  for (size_t i = 0; i < m; ++i)
  {
    res.set(i, data.get(i * n + id));
  }
  return res;
}

Ints Mtx::getRow(size_t id) const
{
  Ints res(n, 0);
  for (size_t j = 0; j < n; ++j)
  {
    res.set(j, data.get(id * n + j));
  }
  return res;
}
