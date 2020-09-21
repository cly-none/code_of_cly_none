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

typedef long double db;
const long double Pi = 3.141592653589793238462643383279502884197169399375105820974944592307816;
db err = 0;

const int MOD = (int)(1e9 + 7);
inline void Add(int& x,int y) {
  x = (x + y >= MOD ? x + y - MOD : x + y);
}
inline void Sub(int &x,int y) {
  x = (x - y < 0 ? x - y + MOD : x - y);
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

db mx = 0;
ll to_ll(db x) {
  mx = max(mx, x);
  return round((long double)x);
  // ll ret = (ll)(floor(x + 0.5) + 0.1);
  // return ret;
}
const int N = 100010;
typedef vector<int> Poly;
namespace MTT {
  struct cpl {
    db u, v;
    cpl(db u=0,db v=0): u(u), v(v) {}
    cpl operator + (const cpl& a) const {
      return cpl(u + a.u, v + a.v);
    }
    cpl operator - (const cpl& a) const {
      return cpl(u - a.u, v - a.v);
    }
    cpl operator * (const cpl& a) const {
      return cpl(u * a.u - v * a.v, u * a.v + v * a.u);
    }
  };
  const int M = 32768;
  int rev[N];
  cpl unit[M + 10];
  void prework(int l) {
    rep (i, 0, l-1)
      if (i&1) rev[i] = rev[i ^ 1] | (l >> 1);
      else rev[i] = rev[i >> 1] >> 1;
    rep (i, 0, l) unit[i] = cpl(cos(2 * Pi * i / l), sin(2 * Pi * i / l));
  }
  void dft(cpl *a,int l,int sgn) {
    rep (i, 0, l-1) if (rev[i] < i)
      swap(a[i], a[rev[i]]);
    cpl w, wp, u, v;
    for (int s = 2; s <= l; s <<= 1) {
      // wp = cpl(cos(2 * (long double)Pi / s), sin(2 * (long double)Pi / s));
      // if (sgn) wp.v = - wp.v;
      for (int k = 0; k < l; k += s) {
        // w = cpl(1, 0);
        for (int j = 0; j < (s >> 1); ++ j) {
	  if (!sgn) w = unit[j * (l / s)];
	  else w = unit[l - j * (l / s)];
          u = a[k + j];
          v = a[k + j + (s >> 1)] * w;
          a[k + j] = u + v;
          a[k + j + (s >> 1)] = u - v;
          // w = w * wp;
        }
      }
    }
    if (sgn) {
      rep (i, 0, l-1) a[i] = cpl(a[i].u / l, a[i].v / l);
    }
  }
  const int B = sqrt(MOD);
  void Mul(int *a,int n,int *b,int m,int *c) {
    static cpl ta[N], tb[N], tc[N], td[N], te[N], tf[N], tg[N];
    int l = 1;
    while (l < n + m - 1) l <<= 1;
    prework(l);
    rep (i, 0, l-1) ta[i] = tb[i] = tc[i] = td[i] = cpl();
    rep (i, 0, n-1) {
      ta[i] = cpl(a[i] / B, 0);
      tb[i] = cpl(a[i] % B, 0);
    }
    rep (i, 0, m-1) {
      tc[i] = cpl(b[i] / B, 0);
      td[i] = cpl(b[i] % B, 0);
    }
    dft(ta, l, 0), dft(tb, l, 0), dft(tc, l, 0), dft(td, l, 0);
    rep (i, 0, l-1) {
      te[i] = ta[i] * tc[i];
      tf[i] = ta[i] * td[i] + tb[i] * tc[i];
      tg[i] = tb[i] * td[i];
      mx = max(mx, te[i].u);
      mx = max(mx, tf[i].u);
      mx = max(mx, tg[i].u);
    }
    dft(te, l, 1), dft(tf, l, 1), dft(tg, l, 1);
    rep (i, 0, n + m - 2) {
      ll tmp = to_ll(te[i].u) % MOD * B % MOD * B % MOD
	+ to_ll(tf[i].u) % MOD * B % MOD
	+ to_ll(tg[i].u);
      c[i] = (tmp % MOD);
      err = max(err, abs(te[i].u - to_ll(te[i].u)));
      err = max(err, abs(tf[i].u - to_ll(tf[i].u)));
      err = max(err, abs(tg[i].u - to_ll(tg[i].u)));
    }
  }
}
Poly operator * (Poly a,Poly b) {
  static int val[N];
  MTT::Mul(a.data(), (int)a.size(), b.data(), (int)b.size(), val);
  return Poly(val, val + (int)a.size() + (int)b.size() - 1);
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

int PolyLimit;
struct Matrix {
  Poly dat[3][3];
  Matrix() {
    rep (i, 1, 2) rep (j, 1, 2) dat[i][j].clear();
  }
  Poly* operator [] (int a) {
    return dat[a];
  }
  Matrix operator * (Matrix& a) {
    Matrix ret;
    rep (i, 1, 2) rep (j, 1, 2) rep (k, 1, 2)
      ret[i][j] = ret[i][j] + (dat[i][k] * a[k][j]);
    rep (i, 1, 2) rep (j, 1, 2)
      ret[i][j].resize(PolyLimit);
    return ret;
  }
  void init_identity() {
    rep (i, 1, 2) rep (j, 1, 2) {
      if (i != j) dat[i][j] = Poly(1, 0);
      else dat[i][j] = Poly(1, 1);
    }
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

int calc(ll l,ll k,int y) {
  PolyLimit = l+1;
  Matrix trans;
  if (y == 1) {
    trans[1][1] = Poly {1};
    trans[1][2] = Poly {0};
  } else if (y == MOD-1) {
    trans[1][1] = Poly {MOD-1, MOD-2};
    trans[1][2] = Poly {0, 2};
  }
  trans[2][1] = Poly {MOD - 1};
  trans[2][2] = Poly {1};
  trans = power(trans, k);
  Poly u = trans[1][1] * (Poly {0, 1}) + trans[1][2];
  Poly v = trans[2][1] * (Poly {0, 1}) + trans[2][2];
  u = u * Inv(v, PolyLimit);
  return u[l];
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
  cerr << (long double)err << endl;
  cerr << (long double)mx << endl;
  return 0;
}
// 10000 10000
// 749784357
// 100 1e12
// 635147632
