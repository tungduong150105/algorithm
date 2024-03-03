template<class T, class Merge = std::plus<T>>
struct SegmentTree {
  int n;
  Merge merge;
  std::vector<T> data;
  SegmentTree(int m = 0) : merge(Merge()) {
    init(m);
  }
  SegmentTree(const std::vector<T>& init) : SegmentTree(int(init.size())) {
    std::function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (r - l == 1) {
        data[p] = init[l];
        return;
      }
      int m = (l + r) / 2;
      build(2 * p, l, m);
      build(2 * p + 1, m, r);
      push(p);
    };
    build(1, 0, n);
  }
  void init(int m) {
    n = m;
    data.assign(4 << std::__lg(n), T());
  }
  void push(int p) {
    data[p] = merge(data[2 * p], data[2 * p + 1]);
  }
  void modify(int p, int l, int r, int x, T v) {
    if (r - l == 1) {
      data[p] = v;
      return;
    }
    int m = (l + r) / 2;
    if (x < m) {
      modify(2 * p, l, m, x, v);
    } else {
      modify(2 * p + 1, m, r, x, v);
    }
    push(p);
  }
  void modify(int x, T v) {
    update(1, 0, n, x, v);
  }
  T rangeQuery(int p, int l, int r, int x, int y) {
    if (l >= y || r <= x) {
      return T();
    }
    if (x <= l && r <= y) {
      return data[p];
    }
    int m = (l + r) / 2;
    return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
  }
  T rangeQuery(int l, int r) {
    return rangeQuery(1, 0, n, l, r);
  }
};
