#include "plot.hpp"

void Plot::set(int x, int y)
{
  p_t p;
  p.x = x;
  p.y = y;
  data_ = data_.append(p); 
}

int Plot::calc(int x) const
{
  for (size_t i = 0; i < data_.getSize(); ++i)
  {
    p_t p = data_.get(i);
    if (p.x == x)
    {
      return p.y;
    }
  }
  return 0; 
}

size_t Plot::solve(Ints & buf, int y) const
{
  size_t cnt = 0;
  for (size_t i = 0; i < data_.getSize(); ++i)
  {
    p_t p = data_.get(i);
    if (p.y == y)
    {
      buf = buf.append(p.x); 
      ++cnt;
    }
  }
  return cnt;
}

Plot Plot::append(p_t p) const
{
  Plot res(*this);
  res.data_ = res.data_.append(p);
  return res;
}
