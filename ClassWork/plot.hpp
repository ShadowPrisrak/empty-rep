#ifndef PLOT_HPP
#define PLOT_HPP
#include "points.hpp"
#include "point.hpp"

class Plot
{
public:
  void set(int x, int y);
  int calc(int x);
  size_t solve(Ints & buf, int y);
  Points append(p_t p);
private:
  Ints data_;
};

#endif
