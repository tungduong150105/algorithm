#include <bits/stdc++.h>
template<class T, class Merge = std::plus<T>>
struct SegmentFull {
  int n;
  T unset;
  Merge merge;
  std::vector<T> data, tag, tag2; // value - add - set
  SegmentFull(int m = 0, T _unset = -1) : merge(Merge()) {
    init(m, _unset);
  }
  SegmentFull(const std::vector<T>& init) : SegmentFull(int(init.size())) {
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
  void init(int m, T _unset) {
    n = m;
    unset = _unset;
    data.assign(4 << std::__lg(n), T());
    tag.assign(4 << std::__lg(n), T());
    tag2.assign(4 << std::__lg(n), unset);
  }
  void push(int p) {
    data[p] = merge(data[2 * p], data[2 * p + 1]);
  }
  void app(int p, int l, int r) {
    int m = (l + r) / 2;
    if (tag2[p] != unset) {
      tag2[2 * p] = tag2[2 * p + 1] = tag2[p];
      data[2 * p] = data[2 * p + 1] = tag2[p];
      tag[2 * p] = tag[2 * p + 1] = 0;
      tag2[p] = unset;
    } else if (tag[p]) {
      if (tag2[2 * p] == unset) {
        tag[2 * p] += tag[p];
      } else {
        tag2[2 * p] += tag[p];
        tag[2 * p] = 0;
      }
      if (tag2[2 * p + 1] == unset) {
        tag[2 * p + 1] += tag[p];
      } else {
        tag2[2 * p + 1] += tag[p];
        tag[2 * p + 1] = 0;
      }
      data[2 * p] += tag[p];
      data[2 * p + 1] += tag[p];
      tag[p] = 0;
    }
  }
  void addRange(int p, int l, int r, int x, int y, T v) {
    if (x >= r || y <= l) {
      return;
    }
    if (x <= l && r <= y) {
      data[p] += v;
      if (tag2[p] == unset) {
        tag[p] += v;
      } else {
        tag2[p] += v;
      }
      return;
    }
    app(p, l, r);
    int m = (l + r) / 2;
    addRange(2 * p, l, m, x, y, v);
    addRange(2 * p + 1, m, r, x, y, v);
    push(p);
  }
  void addRange(int l, int r, T v) {
    addRange(1, 0, n, l, r, v);
  }
  void setRange(int p, int l, int r, int x, int y, T v) {
    if (x >= r || y <= l) {
      return;
    }
    if (x <= l && r <= y) {
      data[p] = v;
      tag2[p] = v;
      tag[p] = 0;
      return;
    }
    app(p, l, r);
    int m = (l + r) / 2;
    setRange(2 * p, l, m, x, y, v);
    setRange(2 * p + 1, m, r, x, y, v);
    push(p);
  }
  void setRange(int l, int r, T v) {
    setRange(1, 0, n, l, r, v);
  }
  T rangeQuery(int p, int l, int r, int x, int y) {
    if (x >= r || y <= l) {
      return T();
    }
    if (x <= l && r <= y) {
      return data[p];
    }
    app(p, l, r);
    int m = (l + r) / 2;
    return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
  }
  T rangeQuery(int l, int r) {
    return rangeQuery(1, 0, n, l, r);
  }
};
