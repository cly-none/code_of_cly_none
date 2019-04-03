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
inline void ckmn(tp& x, tp y) {
  x = x < y ? x : y;
}
template <typename tp>
inline void ckmx(tp& x, tp y) {
  x = x < y ? y : x;
}

const int MOD = (int)(1e9 + 7);
int power(int a,int b) {
  int ret = 1;
  while (b) {
    if (b & 1) ret = 1ll * ret * a % MOD;
    a = 1ll * a * a % MOD;
    b >>= 1;
  }
  return ret;
}
const int M = 110, MAX = 100000, B = 1000;
int isp[MAX + 10], pri[MAX], pcnt;
int cmb[M][M];
void prework() {
  rep (i, 2, MAX) {
    if (!isp[i]) pri[++pcnt] = i;
    for (int j = 1 ; pri[j] * i <= MAX ; ++ j) {
      isp[pri[j] * i] = 1;
      if (i % pri[j] == 0) break;
    }
  }
  int m = 100;
  rep (i, 0, m) cmb[i][0] = 1;
  rep (i, 1, m) rep (j, 1, i)
    cmb[i][j] = (cmb[i-1][j] + cmb[i-1][j-1]) % MOD;
}
int getnum(vector<pii>& a, vector<pii>& b) {
  int ret = 0;
  for (int i = 0 ; i < (int)a.size() ; ++ i)
    for (int j = 0 ; j < (int)b.size() ; ++ j) {
      ret += 1ll * a[i].sec * b[j].sec * __gcd(a[i].fir, b[j].fir) % (MOD-1);
      ret %= MOD-1;
    }
  return ret;
}
vector<pii> vec[2][B];
int cnt[2], fac[B], num[B], fcnt, rec[2][B];
void dfs(int p, int val, int phi, int sgn, int n) {
  if (p > fcnt) {
    ++ cnt[sgn];
    vec[sgn][cnt[sgn]].push_back(pii(val, n / val));
    rec[sgn][cnt[sgn]] = phi;
    return;
  }
  dfs(p + 1, val, phi, sgn, n);
  val *= fac[p], phi *= fac[p] - 1;
  rep (i, 1, num[p]) {
    dfs(p + 1, val, phi, sgn, n);
    if (i < num[p]) {
      val *= fac[p];
      phi *= fac[p];
    }
  }
}
void gene_per(int n, int sgn) {
  rep (i, 1, cnt[sgn]) vec[sgn][i].clear(), rec[sgn][i] = 0;
  cnt[sgn] = 0;
  fcnt = 0;
  int tmp = n;
  for (int i = 1 ; 1ll * pri[i] * pri[i] <= tmp ; ++ i) {
    if (tmp % pri[i]) continue;
    fac[++fcnt] = pri[i], num[fcnt] = 0;
    while (tmp % pri[i] == 0) ++ num[fcnt], tmp /= pri[i];
  }
  if (tmp != 1) fac[++fcnt] = tmp, num[fcnt] = 1;
  dfs(1, 1, 1, sgn, n);
  if (n & 1) {
    ++ cnt[sgn];
    vec[sgn][cnt[sgn]].push_back(pii(1, 1));
    vec[sgn][cnt[sgn]].push_back(pii(2, n >> 1));
    rec[sgn][cnt[sgn]] = n;
  } else {
    ++ cnt[sgn];
    vec[sgn][cnt[sgn]].push_back(pii(2, n >> 1));
    rec[sgn][cnt[sgn]] = n >> 1;
    ++ cnt[sgn];
    vec[sgn][cnt[sgn]].push_back(pii(1, 2));
    vec[sgn][cnt[sgn]].push_back(pii(2, (n >> 1) - 1));
    rec[sgn][cnt[sgn]] = n >> 1;
  }
}
/*
 * brute force
 rep (i, 1, n) rep (j, 1, m) {
 int a = __gcd(i, n);
 int b = __gcd(j, m);
 (ret += power(col, a * b * __gcd(n/a, m/b))) %= MOD;
 }
 rep (j, 1, m) {
 int b = __gcd(j, m);
 if (n & 1) {
 ret += 1ll * n * power(col, b * (__gcd(1, m/b) + (n >> 1) * __gcd(2, m/b))) % MOD;
 } else {
 ret += 1ll * (n >> 1) * power(col, b * ((n >> 1) * __gcd(2, m/b))) % MOD;
 ret += 1ll * (n >> 1) * power(col, b * (2 * __gcd(1, m/b) + ((n>>1)-1) * __gcd(2, m/b))) % MOD;
 ret %= MOD;
 }
 }
 rep (i, 1, n) {
 int a = __gcd(i, n);
 if (m & 1) {
 ret += 1ll * m * power(col, a * (__gcd(1, n/a) + (m >> 1) * __gcd(2, n/a))) % MOD;       
 } else {
 ret += 1ll * (m >> 1) * power(col, a * ((m >> 1) * __gcd(2, n/a))) % MOD;
 ret += 1ll * (m >> 1) * power(col, a * (2 * __gcd(1, n/a) + ((m>>1)-1) * __gcd(2, n/a))) % MOD;
 ret %= MOD;      
 }
 }
 vec[0].clear(), vec[1].clear();
 if (n & 1) {
 vec[0].push_back(pii(1, 1));
 vec[0].push_back(pii(2, n>>1));
 }
 if (m & 1) {
 vec[1].push_back(pii(1, 1));
 vec[1].push_back(pii(2, m>>1));
 }
 if ((n & 1) && (m & 1)) {
 ret += 1ll * n * m % MOD * power(col, getnum()) % MOD;
 ret %= MOD;
 } else if (n & 1) {
 vec[1].push_back(pii(2, m >> 1));
 ret += 1ll * n * (m>>1) % MOD * power(col, getnum()) % MOD;
 vec[1][0] = pii(2, (m >> 1) - 1);
 vec[1].push_back(pii(1, 2));
 ret += 1ll * n * (m>>1) % MOD * power(col, getnum()) % MOD;
 } else if (m & 1) {
 vec[0].push_back(pii(2, n >> 1));
 ret += 1ll * (n>>1) * m % MOD * power(col, getnum()) % MOD;
 vec[0][0] = pii(2, (n >> 1) - 1);
 vec[0].push_back(pii(1, 2));
 ret += 1ll * (n>>1) * m % MOD * power(col, getnum()) % MOD;    
 } else {
 rep (a, 0, 1) rep (b, 0, 1) {
 vec[0].clear(), vec[1].clear();
 if (a == 0) vec[0].push_back(pii(2, n>>1));
 else {
 vec[0].push_back(pii(2, (n >> 1) - 1));
 vec[0].push_back(pii(1, 2));
 }
 if (b == 0) vec[1].push_back(pii(2, m>>1));
 else {
 vec[1].push_back(pii(2, (m >> 1) - 1));
 vec[1].push_back(pii(1, 2));
 }
 ret += 1ll * (n >> 1) * (m >> 1) % MOD * power(col, getnum()) % MOD;
 }
 }
 ret = 1ll * ret * power(4ll * n * m % MOD, MOD - 2) % MOD;
*/
int solve(int n,int m,int col) {
  int ret = 0;
  gene_per(n, 0);
  gene_per(m, 1);
  rep (i, 0, col) {
    int tmp = 0;
    rep (a, 1, cnt[0]) rep (b, 1, cnt[1]) {
      tmp += 1ll * rec[0][a] * rec[1][b] % MOD * power(i, getnum(vec[0][a], vec[1][b])) % MOD;
      if (tmp >= MOD) tmp -= MOD;
    }
    if ((col - i) & 1) (ret -= 1ll * tmp * cmb[col][i] % MOD) %= MOD;
    else (ret += 1ll * tmp * cmb[col][i] % MOD) %= MOD;
  }
  ret = 1ll * ret * power(4ll * n * m % MOD, MOD - 2) % MOD;
  return ret;
}
int fib[50];
int main() {
  ll ans = 0;
  prework();
  fib[0] = 0, fib[1] = 1;
  rep (i, 2, 40) fib[i] = fib[i-1] + fib[i-2];
  rep (i, 4, 40) (ans += solve(fib[i-1], fib[i], i)) %= MOD;
  ans = (ans % MOD + MOD) % MOD;
  cout << ans << endl;
  return 0;
}
