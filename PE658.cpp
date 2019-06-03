#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef double db;
#define fir first
#define sec second
#define rep(i,a,b) for (int i = (a) ; i <= (b) ; ++ i)
#define rrp(i,a,b) for (int i = (a) ; i >= (b) ; -- i)
#define gc() getchar()
template <typename tp>
inline void read(tp& x) {
  x = 0; char tmp; bool key = 0;
  for (tmp = gc() ; !isdigit(tmp) ; tmp = gc())
    key = (tmp == '-');
  for ( ; isdigit(tmp) ; tmp = gc())
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
int power(int a,int b) {
  int ret = 1;
  while (b) {
    if (b&1) ret = (int) (1ll * ret * a % MOD);
    a = (int) (1ll * a * a % MOD);
    b >>= 1;
  }
  return ret;
}
inline void Add(int& x,int y) {
  x = x + y >= MOD ? x + y - MOD : x + y;
}
inline void Sub(int& x,int y) {
  x = x - y < 0 ? x - y + MOD : x - y;
}

const int N = (int)1e7 + 10;
int jc[N], inv[N];
int comb(int a,int b) {
  if (a < 0 || b < 0 || a < b) return 0;
  return 1ll * jc[a] * inv[b] % MOD * inv[a-b] % MOD;
}
ll m = (ll)1e12, n = (ll)1e7;
int ans = 0, f[N];
int calc(int v,ll m) {
  if (v == 0) return m >= 0;
  if (v == 1) return (m+1) % MOD;
  return 1ll * (power(v, (m+1) % (MOD-1)) - 1) * power(v - 1, MOD - 2) % MOD;
}
int main() {
  jc[0] = 1;
  rep (i, 1, n) jc[i] = 1ll * jc[i-1] * i % MOD;
  inv[n] = power(jc[n], MOD - 2);
  rrp (i, n-1, 0) inv[i] = 1ll * inv[i+1] * (i+1) % MOD;

  f[0] = (n % 2 == 0) ? 1 : 0;
  // define f[i] = \sum_{k=0}^{n-i} (-1)^k \comb {k+i} {i}
  // we have 2f[i] = f[i-1] + (-1)^{n-i} \comb n {i-1} + (-1)^{n-i} \comb n i
  rep (i, 1, n) {
    int tmp = comb(n, i-1);
    Add(tmp, comb(n, i));
    if ((n-i)&1) tmp = MOD - tmp;
    Add(tmp, f[i-1]);
    f[i] = 1ll * tmp * (MOD + 1) / 2 % MOD;
  }
  rep (i, 1, n)
    Add(ans, 1ll * f[i] * calc(i, m) % MOD);
  if (n&1) Sub(ans, calc(0, m));
  ans = MOD - ans;
  rep (i, 1, n) Add(ans, calc(i, m));
  printf("%d\n", ans);
  return 0;
}
