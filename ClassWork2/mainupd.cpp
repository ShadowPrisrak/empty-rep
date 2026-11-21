#include <iostream>
#include <stdexcept>

const size_t planarSize = 5;
const int planarTypes[planarSize] = {1, 2, 3, 4, 5};

namespace arch {
  enum Color {RED, GREEN, BLUE};

  Color makeColor(char c) {
    switch (c) {
    case 'r': return Color::RED;
    case 'g': return Color::GREEN;
    case 'b': return Color::BLUE;
    default: throw std::logic_error("Incorrect color");
    }
  }

  class Planar;
  class Colored;
  class Point;
  class Vector;
  class ColoredPoint;
  class Brush;
  class Circle;
  class ColoredCircle;

  class Planar {
  public:
    virtual ~Planar() = default;
    virtual std::ostream& info(std::ostream& out) = 0;
    virtual int x() const = 0;
    virtual int y() const = 0;
    virtual int abs_sqr() const = 0; 
  };

  class Colored {
  public:
    virtual ~Colored() = default;
    virtual Color getColor() const = 0;
    virtual void setColor(Color color) = 0;
  };

  class Point: public Planar {
  public:
    Point(int x, int y): x_(x), y_(y) {}
    virtual ~Point() = default;
    virtual std::ostream& info(std::ostream& out) override { return out << "Point"; }
    virtual int x() const override { return x_; }
    virtual int y() const override { return y_; }
    virtual int abs_sqr() const override { return x_ * x_ + y_ * y_; }
  private:
    int x_, y_;
  };

  class Vector: public Planar {
  public:
    Vector(Point a, Point b): a_(a), b_(b) {}
    virtual ~Vector() = default;
    virtual std::ostream& info(std::ostream& out) override { return out << "Vector"; }
    virtual int x() const override { return b_.x() - a_.x(); }
    virtual int y() const override { return b_.y() - a_.y(); }
    virtual int abs_sqr() const override { return (x() * x() + y() * y()); }
  private:
    Point a_, b_;
  };

  class ColoredPoint: public Planar, public Colored {
  public:
    ColoredPoint(Point p, Color color): p_(p), cl_(color) {}
    virtual ~ColoredPoint() = default;
    virtual std::ostream& info(std::ostream& out) override { return out << "Colored point"; }
    virtual int x() const override { return p_.x(); }
    virtual int y() const override { return p_.y(); }
    virtual int abs_sqr() const override { return p_.abs_sqr(); }
    virtual Color getColor() const override { return cl_; }
    virtual void setColor(Color color) override { cl_ = color; }
  private:
    Point p_;
    Color cl_;
  };

  class Brush: public Colored {
  public:
    Brush(Color color): cl_(color) {}
    virtual ~Brush() = default;
    virtual Color getColor() const override { return cl_; }
    virtual void setColor(Color color) override { cl_ = color; }
  private:
    Color cl_;
  };

  class Circle: public Planar {
  public:
    Circle(Point c, int r): c_(c), r_(r) {}
    virtual ~Circle() = default;
    virtual std::ostream& info(std::ostream& out) override { return out << "Circle"; }
    virtual int x() const override { return c_.x(); }
    virtual int y() const override { return c_.y(); }
    virtual int abs_sqr() const override { return r_ * r_; }
    double sqr() const { return 3.14159265358979323846 * r_ * r_; }
    void move(Point p) { c_ = p; }
    void resize(int r) { r_ = r; }
  private:
    Point c_;
    int r_;
  };

  class ColoredCircle: public Planar, public Colored {
  public:
    ColoredCircle(Circle cir, Color cl): cir_(cir), cl_(cl) {}
    virtual ~ColoredCircle() = default;
    virtual std::ostream& info(std::ostream& out) override { return out << "Colored circle"; }
    virtual int x() const override { return cir_.x(); }
    virtual int y() const override { return cir_.y(); }
    virtual int abs_sqr() const override { return cir_.abs_sqr(); }
    double sqr() const { return cir_.sqr(); }
    virtual Color getColor() const override { return cl_; }
    virtual void setColor(Color color) override { cl_ = color; }
    void move(Point p) { cir_.move(p); }
  private:
    Circle cir_;
    Color cl_;
  };

  Planar* cloneCircle(std::istream& in) {
    int x = 0, y = 0, r = 0;
    if (in >> x >> y >> r) {
      return new Circle(Point(x, y), r);
    }
    throw std::logic_error("Incorrect circle");
  }

  ColoredCircle* cloneColoredCircle(std::istream& in) {
    int x = 0, y = 0, r = 0;
    char color = 0;
    if (in >> x >> y >> r >> color) {
      return new ColoredCircle(Circle(Point(x, y), r), makeColor(color));
    }
    throw std::logic_error("Incorrect colored circle");
  }

  Planar* cloneColoredCirclePlanar(std::istream& in) { return cloneColoredCircle(in); }
  Colored* cloneColoredCircleColored(std::istream& in) { return cloneColoredCircle(in); }
}

namespace fabric {
  class AbstractFabricPlanar {
  public:
    virtual ~AbstractFabricPlanar() = default;
    virtual arch::Planar* create(std::istream& in) = 0;
  };

  class FabricPoint: public AbstractFabricPlanar {
  public:
    virtual arch::Planar* create(std::istream& in) override {
      int x = 0, y = 0;
      if (in >> x >> y) return new arch::Point(x, y);
      throw std::logic_error("Incorrect point");
    }
  };

  class FabricVector: public AbstractFabricPlanar {
  public:
    virtual arch::Planar* create(std::istream& in) override {
      int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
      if (in >> x1 >> y1 >> x2 >> y2) return new arch::Vector(arch::Point(x1, y1), arch::Point(x2, y2));
      throw std::logic_error("Incorrect vector");
    }
  };

  class FabricColoredPoint: public AbstractFabricPlanar {
  public:
    virtual arch::Planar* create(std::istream& in) override {
      int x = 0, y = 0;
      char color = 0;
      if (in >> x >> y >> color) return new arch::ColoredPoint(arch::Point(x, y), arch::makeColor(color));
      throw std::logic_error("Incorrect colored point");
    }
  };

  class FabricCircle: public AbstractFabricPlanar {
  public:
    virtual arch::Planar* create(std::istream& in) override {
      int x = 0, y = 0, r = 0;
      if (in >> x >> y >> r) return new arch::Circle(arch::Point(x, y), r);
      throw std::logic_error("Incorrect circle");
    }
  };

  class FabricColoredCircle: public AbstractFabricPlanar {
  public:
    virtual arch::Planar* create(std::istream& in) override {
      int x = 0, y = 0, r = 0;
      char color = 0;
      if (in >> x >> y >> r >> color) return new arch::ColoredCircle(arch::Circle(arch::Point(x, y), r), arch::makeColor(color));
      throw std::logic_error("Incorrect colored circle");
    }
  };

  void clearFabricsPlanar(AbstractFabricPlanar** fabricsPlanar, size_t size) {
    for (size_t j = 0; j < size; j++) {
      delete fabricsPlanar[j];
    }
    delete[] fabricsPlanar;
  }

  AbstractFabricPlanar** makeFabricsPlanar() {
    AbstractFabricPlanar** fabricsPlanar = new AbstractFabricPlanar*[planarSize];
    size_t i = 0;
    try {
      fabricsPlanar[i++] = new FabricPoint();
      fabricsPlanar[i++] = new FabricVector();
      fabricsPlanar[i++] = new FabricColoredPoint();
      fabricsPlanar[i++] = new FabricCircle();
      fabricsPlanar[i++] = new FabricColoredCircle();
    }
    catch (const std::exception&) {
      clearFabricsPlanar(fabricsPlanar, i);
    }
    return fabricsPlanar;
  }
}

std::ostream& printAbsSqr(std::ostream& out, arch::Planar* pl) {
  return pl->info(out) << ' ' << pl->abs_sqr();
}

void clear(arch::Planar* pls[], size_t size) {
  for (size_t i = 0; i < size; i++) {
    delete pls[i];
  }
  delete[] pls;
}

int main() {
  size_t cap = 0;
  fabric::AbstractFabricPlanar** fabrics = fabric::makeFabricsPlanar();
  
  if (!(std::cin >> cap)) {
    std::cerr << "Incorrect size\n";
    return 1;
  }

  arch::Planar** pls = nullptr;
  try {
    pls = new arch::Planar*[cap];
  }
  catch (const std::exception& e) {
    fabric::clearFabricsPlanar(fabrics, planarSize);
    std::cerr << e.what() << '\n';
    return 1;
  }
  
  size_t size = 0;
  while (size < cap && std::cin) {
    int num = 0;
    if (!(std::cin >> num)) break;

    try {
      bool created = false;
      for (size_t j = 0; j < planarSize; j++) {
        if (num == planarTypes[j]) {
          pls[size] = fabrics[j]->create(std::cin);
          size++;
          created = true;
          break;
        }
      }
      if (!created) throw std::logic_error("Incorrect type");
    }
    catch (const std::exception& e) {
      fabric::clearFabricsPlanar(fabrics, planarSize);
      clear(pls, size);
      std::cerr << e.what() << '\n';
      return 1;
    }
  }

  for (size_t i = 0; i < size; i++) {
    printAbsSqr(std::cout, pls[i]) << '\n';
  }

  fabric::clearFabricsPlanar(fabrics, planarSize);
  clear(pls, size);

  return 0;
}

// 1 - Point [x, y]
// 2 - Vector [x1, y1, x2, y2]
// 3 - ColoredPoint [x, y, color]
// 4 - Circle [x, y, r]
// 5 - ColoredCircle [x, y, r, color]
