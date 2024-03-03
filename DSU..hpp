struct DSU {
  bool small_to_large;
  std::vector<int> f;
  DSU(int m = 0, bool _small_to_large = false) {
    init(m, _small_to_large);
  }
  void init(int m, bool _small_to_large) {
    small_to_large = _small_to_large;
    f.assign(m, -1);
  }
  int leader(int x) {
    if (f[x] < 0) {
      return x;
    }
    return f[x] = leader(f[x]);
  }
  int size(int x) {
    return -f[leader(x)];
  }
  bool same(int u, int v) {
    return leader(u) == leader(v);
  }
  bool merge(int u, int v) {
    u = leader(u), v = leader(v);
    if (u == v) {
      return false;
    }
    if (small_to_large && f[u] > f[v]) {
      std::swap(u, v);
    }
    f[u] += f[v];
    f[v] = u;
    return true;
  }
};
