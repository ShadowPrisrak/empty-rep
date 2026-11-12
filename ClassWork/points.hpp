#ifndef POINTS_HPP
#define POINTS_HPP

#include "ints.hpp"
#include "point.hpp"

class Points
{
public:
  Points();
  void set(size_t id, p_t p);
  p_t get(size_t id) const;
  Points append(p_t p);
  size_t getSize() const;

private:
  Ints data_; 
};

#endif
