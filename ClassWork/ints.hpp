#ifndef INTS_HPP
#define INTS_HPP
#include <cstddef>

class Ints
{
public:
  Ints();
  Ints(size_t size, int value);
  Ints(const Ints & rhs); //копирование
  Ints(Ints && rhs) noexcept; //перемещение
  Ints & operator=(const Ints & rhs); //1
  Ints & operator=(Ints && rhs) noexcept; //2
  ~Ints(); //деструктор

  Ints operator+(const Ints & rhs) const;

  size_t getSize() const noexcept;
  void set(size_t id, int i) noexcept;
  int get(size_t id) const noexcept;
  void setSafe(size_t id, int i);
  int getSafe(size_t id) const;

  Ints append(int i);
  Ints append(Ints b);

private:
  void resize();
  size_t capacity_;
  size_t size_;
  int * data_;
};
#endif

