/*
 *step1: we can proof that if A * T_n + B = T_m for pair (A,B), then m can be written into form cn+d.
 *step2: after calculating the expression, since gcd(k-4,k-2)=1, we have
 *A=((2k-4)i+1)^2, B=1/2 * (4-k)^2 * i(ki-1) for any positive integer i.
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
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


int main() {
  ll n = 1e12;
  ll ans = 0;
  for (ll k = 3; k <= n; k += 2) {
    ll va = (ll)(4 - k) * (4 - k);
    ll vb = 8 * (k - 2);
    ll g = __gcd(va, vb);
    va /= g;
    vb /= g;
    int key = 0;
    for (ll c = 2; c * c <= n; ++ c) {
      ll a = c * c;
      if ((va * (a - 1)) % vb) continue;
      if ((4 - k) * (c - 1) % (2 * k - 4)) continue;
      ll b = (va * (a - 1)) / vb;
      if (b > n) break;
      ans += a + b;
      key = 1;
    }
    if (!key) {
      cerr << k << endl;
      break;
    }
  }
  cout << ans << endl;
  return 0;
}
