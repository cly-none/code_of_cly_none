#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define fir first
#define sec second
#define rep(i,a,b) for (int i = (a); i <= (b); ++ i)
#define rrp(i,a,b) for (int i = (a); i >= (b); -- i)
#define gc() getchar()
template <typename tp>
inline void read(tp& x) {
  x = 0; char tmp; bool key = 0;
  for (tmp = gc(); !isdigit(tmp); tmp = gc())
    key = (tmp == '-');
  for (; isdigit(tmp); tmp = gc())
    x = (x << 3) + (x << 1) + (tmp ^ '0');
  if (key) x = -x;
}
template <typename tp>
inline void ckmn(tp& x,tp y) {
  x = x < y ? x : y;
}
template <typename tp>
inline void ckmx(tp& x,tp y) {
  x = x < y ? y : x;
}

const int MOD = (int)(1e9 + 7);
inline void Add(int& x,int y) {
  x = x + y >= MOD ? x + y - MOD : x + y;
}
inline void Sub(int& x,int y) {
  x = x - y < 0 ? x - y + MOD : x - y;
}
int power(int a,int b) {
  int ret = 1;
  while (b) {
    if (b&1) ret = (ll)ret * a % MOD;
    a = (ll)a * a % MOD;
    b >>= 1;
  }
  return ret;
}

/*
f_k(x, y) = (1 / (1 - f_{k-1}(x, y)) - 1 - x) * y + x
*/

const int N = 200;
int sz;
struct Matrix {
  int dat[N][N];
  Matrix() {
    memset(dat, 0, sizeof dat);
  }
  int* operator [] (int id) {
    return dat[id];
  }
  Matrix operator * (Matrix& a) {
    Matrix ret;
    rep (i, 1, sz) rep (j, 1, sz) rep (k, 1, sz) {
      Add(ret[i][j], (ll)dat[i][k] * a[k][j] % MOD);
    }
    return ret;
  }
  void init_identity() {
    rep (i, 1, sz) rep (j, 1, sz)
      dat[i][j] = (i == j);
  }
};
Matrix power(Matrix a,ll b) {
  Matrix ret;
  ret.init_identity();
  while (b) {
    if (b&1) ret = ret * a;
    a = a * a;
    b >>= 1;
  }
  return ret;
}
typedef vector<int> Poly;
Poly operator * (Poly a,Poly b) {
  Poly ret((int)a.size() + (int)b.size() - 1);
  rep (i, 0, (int)a.size()-1) rep (j, 0, (int)b.size()-1)
    Add(ret[i + j], (ll)a[i] * b[j] % MOD);
  return ret;
}
Poly operator + (Poly a,Poly b) {
  Poly ret(max(a.size(), b.size()));
  rep (i, 0, (int)a.size()-1) Add(ret[i], a[i]);
  rep (i, 0, (int)b.size()-1) Add(ret[i], b[i]);
  return ret;
}
Poly operator - (Poly a,Poly b) {
  Poly ret(max(a.size(), b.size()));
  rep (i, 0, (int)a.size()-1) Add(ret[i], a[i]);
  rep (i, 0, (int)b.size()-1) Sub(ret[i], b[i]);
  return ret;
}
Poly Inv(Poly a,int sz) {
  Poly ret(sz, 0);
  ret[0] = power(a[0], MOD - 2);
  rep (i, 1, sz-1) {
    rep (j, 1, min(i, (int)a.size()-1)) Sub(ret[i], (ll)ret[i-j] * a[j] % MOD);
    ret[i] = (ll)ret[i] * power(a[0], MOD - 2) % MOD;
  }
  return ret;
}
// case 1: l <= 10^12, k <= 100
int calc(ll l,ll k,int y) {
  Poly u(2), v(1, 1);
  u[1] = 1;
  rep (_, 1, k) {
    u = v - u;
    Poly tmp(2, 1);
    v = v - (tmp * u);
    v = v * Poly(1, y);
    tmp[0] = 0, tmp[1] = 1;
    v = v + (tmp * u);
    swap(u, v);
  }
  while (!v.back()) v.pop_back();
  Poly scalar(1, MOD - power(v[0], MOD - 2));
  u = u * scalar;
  v = v * scalar;
  int rec = max((int)u.size(), (int)v.size() - 1);
  u = u * Inv(v, rec), u.resize(rec);
  if (l < (int)u.size()) return u[l];
  sz = (int)v.size() - 1;
  Matrix recur;
  rep (i, 1, sz) recur[1][i] = v[i];
  rep (i, 2, sz) recur[i][i-1] = 1;
  recur = power(recur, l - (rec - 1));
  int ret = 0;
  rep (i, 1, sz) Add(ret, (ll)recur[1][i] * u[rec - i] % MOD);
  return ret;
}
int solve(ll l,ll k) {
  int ret = (ll)(calc(l, k, 1) + calc(l, k, MOD-1)) * power(2, MOD - 2) % MOD;
  return ret;
}
int main() {
  ll w, h;
  cin >> w >> h;
  int ans = solve(w + 1, h) - solve(w + 1, h - 1);
  ans = (ans + MOD) % MOD;
  cout << ans << endl;
  return 0;
}

// 1e12 100
// 364553235
