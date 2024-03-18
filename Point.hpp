template <typename T>
struct Point {
  T x, y;
  Point(const T &x_ = 0, const T &y_ = 0) : x(x_), y(y_) {}
  Point operator-() const {
    return Point(-x, -y);
  }
  Point &operator+=(const Point &lhs) {
    x += lhs.x;
    y += lhs.y;
    return *this;
  }
  Point &operator-=(const Point &lhs) {
    x -= lhs.x;
    y -= lhs.y;
    return *this;
  }
  Point &operator*=(const T &lhs) {
    x *= lhs;
    y *= lhs;
    return *this;
  }
  Point &operator/=(const T &lhs) {
    x /= lhs;
    y /= lhs;
    return *this;
  }
  friend Point operator+(const Point &lhs, const Point &rhs) {
    Point res = lhs;
    res += rhs;
    return res;
  }
  friend Point operator-(const Point &lhs, const Point &rhs) {
    Point res = lhs;
    res -= rhs;
    return res;
  }
  friend Point operator*(const Point &lhs, const T &rhs) {
    Point res = lhs;
    res *= rhs;
    return res;
  }
  friend Point operator/(const Point &lhs, const T &rhs) {
    Point res = lhs;
    res /= rhs;
    return res;
  }
  friend bool operator==(const Point &lhs, const Point &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
  friend bool operator!=(const Point &lhs, const Point &rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y;
  }
  friend std::istream &operator>>(std::istream &is, Point& lhs) {
    return is >> lhs.x >> lhs.y;
  }
  friend std::ostream &operator<<(std::ostream &os, const Point &lhs) {
    return os << "(" << lhs.x << ", " << lhs.y << ")";
  }
  friend T dot(const Point &lhs, const Point &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
  friend T cross(const Point &lhs, const Point &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
};

template <typename T>
T dot(const Point<T> &lhs, const Point<T> &rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}
template <typename T>
T cross(const Point<T> &lhs, const Point<T> &rhs) {
  return lhs.x * rhs.y - lhs.y * rhs.x;
}
template <typename T>
T norm(const Point<T> &lhs) {
  return lhs.x * lhs.x + lhs.y * lhs.y;
}
template <typename T>
T abs(const Point<T> &lhs) {
  return std::sqrt(norm(lhs));
}
template <typename T>
T arg(const Point<T> &lhs) {
  return std::atan2(lhs.y, lhs.x);
}
