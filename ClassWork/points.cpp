#include "points.hpp"

Points::Points():
  data_()
{}

void Points::set(size_t id, p_t p)
{
  data_.set(id * 2, p.x);
  data_.set(id * 2 + 1, p.y);
}

p_t Points::get(size_t id) const
{
  p_t res;
  res.x = data_.get(id * 2);
  res.y = data_.get(id * 2 + 1);
  return res;
}

Points Points::append(p_t p)
{
  Points res(*this);
  res.data_ = res.data_.append(p.x);
  res.data_ = res.data_.append(p.y);
  return res;
}

size_t Points::getSize() const
{
  return data_.getSize() / 2;
}
