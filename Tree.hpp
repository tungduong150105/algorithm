template <class T, class Merge = std::plus<T>>
struct Tree {
  Merge merge;
  int n, curChain, curPos;
  std::vector<std::vector<int>> e;
  SegmentTree<T, Merge> seg;
  std::vector<int> par, dep, sz, chainHead, chainID, pos, arr;
  Tree(int m = 0) : merge(Merge()) {
    init(m);
  }
  void init(int m) {
    n = m + 5;
    curChain = 0;
    curPos = 1;
    e.resize(n);
    par.resize(n);
    dep.resize(n);
    sz.resize(n);
    chainHead.assign(n, -1);
    chainID.resize(n);
    pos.resize(n);
    arr.resize(n);
    seg.init(n);
  }
  void add_edge(int u, int v) {
    e[u].push_back(v);
    e[v].push_back(u);
  }
  void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : e[u]) {
      if (v == p) {
        continue;
      }
      par[v] = u;
      dep[v] = dep[u] + 1;
      dfs(v, u);
      sz[u] += sz[v];
    }
  }
  void hld(int u, int p) {
    if (chainHead[curChain] == -1) {
      chainHead[curChain] = u;
    }
    chainID[u] = curChain;
    pos[u] = curPos;
    arr[curPos] = u;
    ++curPos;
    int nxt = -1;
    for (int v : e[u]) {
      if (v == p) {
        continue;
      }
      if (nxt == -1 || sz[v] > sz[nxt]) {
        nxt = v;
      }
    }
    if (nxt != -1) {
      hld(nxt, u);
    }
    for (int v : e[u]) {
      if (v == p || v == nxt) {
        continue;
      }
      ++curChain;
      hld(v, u);
    }
  }
  int lca(int u, int v) {
    while (chainID[u] != chainID[v]) {
      if (chainID[u] > chainID[v]) {
        u = par[chainHead[chainID[u]]];
      } else {
        v = par[chainHead[chainID[v]]];
      }
    }
    if (dep[u] < dep[v]) {
      return u;
    }
    return v;
  }
  void update(int x, T v) {
    seg.modify(pos[x], v);
  }
  void updateRange(int u, int v, T x) {
    int f = lca(u, v);
    while (chainID[u] != chainID[f]) {
      seg.setRange(pos[chainHead[chainID[u]]], pos[u] + 1, x);
      u = par[chainHead[chainID[u]]];
    }
    while (chainID[v] != chainID[f]) {
      seg.setRange(pos[chainHead[chainID[v]]], pos[v] + 1, x);
      v = par[chainHead[chainID[v]]];
    }
    if (dep[u] < dep[v]) {
      seg.setRange(pos[u], pos[v] + 1, x);
    } else {
      seg.setRange(pos[v], pos[u] + 1, x);
    }
  }
  T rangeQuery(int u, int v) {
    T ans = T();
    int f = lca(u, v);
    while (chainID[u] != chainID[f]) {
      ans = merge(ans, seg.rangeQuery(pos[chainHead[chainID[u]]], pos[u] + 1));
      u = par[chainHead[chainID[u]]];
    }
    while (chainID[v] != chainID[f]) {
      ans = merge(ans, seg.rangeQuery(pos[chainHead[chainID[v]]], pos[v] + 1));
      v = par[chainHead[chainID[v]]];
    }
    if (dep[u] < dep[v]) {
      ans = merge(ans, seg.rangeQuery(pos[u], pos[v] + 1));
    } else {
      ans = merge(ans, seg.rangeQuery(pos[v], pos[u] + 1));
    }
    return ans;
  }
};
