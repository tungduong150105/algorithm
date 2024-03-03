template <typename T>
struct FenwickTree {
  int n;
  std::vector<T> a;
  FenwickTree(int m = 0) {
    init(m);
  }
  void init(int m) {
    n = m;
    a.resize(m, T());
  }
  void add(int p, T v) {
    for (int i = p + 1; i <= n; i += i & -i) {
      a[i - 1] += v;
    }
  }
  T sum(int p) {
    T ans = T();
    for (int i = p; i > 0; i -= i & -i) {
      ans += a[i - 1];
    }
    return ans;
  }
  T rangeSum(int l, int r) {
    return sum(r) - sum(l);
  }
};
