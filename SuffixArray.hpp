struct SuffixArray {
  int n;
  std::vector<int> sa, rk, tmp, lcp;
  SuffixArray(const std::string &s) : n(int(s.size())) {
    sa.resize(n + 1);
    rk.resize(n + 1);
    lcp.resize(n + 1);
    tmp.resize(n + 1);
    for (int i = 0; i <= n; ++i) {
      sa[i] = i;
      rk[i] = i < n ? s[i] : -1;
    }
    for (int k = 1; k <= n; k *= 2) {
      auto Cmp = [&](const int &lhs, const int &rhs) {
        if (rk[lhs] != rk[rhs]) {
          return rk[lhs] < rk[rhs];
        }
        int nlhs = lhs + k <= n ? rk[lhs + k] : -1;
        int nrhs = rhs + k <= n ? rk[rhs + k] : -1;
        return nlhs < nrhs;
      };
      std::sort(sa.begin(), sa.end(), Cmp);
      tmp = rk;
      tmp[sa[0]] = 0;
      for (int i = 1; i <= n; ++i) {
        tmp[sa[i]] = tmp[sa[i - 1]] + Cmp(sa[i - 1], sa[i]);
      }
      rk = tmp;
    }
    for (int i = 0; i <= n; ++i) {
      rk[sa[i]] = i;
    }
    for (int i = 0, k = 0; i < n; ++i, k ? k-- : 0) {
      if (rk[i] == n) {
        k = 0;
        continue;
      }
      int j = sa[rk[i] + 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
        ++k;
      }
      lcp[rk[i]] = k;
    }
  }
};
