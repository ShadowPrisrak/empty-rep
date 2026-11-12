#ifndef MTX_HPP
#define MTX_HPP

#include "ints.hpp" //
#include <cstddef>

class Mtx
{
public:
  Mtx();
  Mtx(size_t m, size_t n);
  ~Mtx() = default;
  
  Mtx sum(const Mtx & oth) const;
  Mtx mul(const Mtx & oth) const;
  Mtx transpose() const;
  int det() const;
  Mtx add_row(int init) const;
  
  Ints getCol(size_t id) const;
  Ints getRow(size_t id) const;

private:
  size_t m;
  size_t n;
  Ints data;
};

#endif
