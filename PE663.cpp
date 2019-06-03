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

const int N = 10000010;
int n = 10000003, lb = 10000001, rb = 10200000;
ll val[N];
int arr[N * 3];
struct node {
  ll sum, lmx, rmx, ans;
} t[N << 2];
void push_up(int x) {
  t[x].sum = t[x<<1].sum + t[x<<1|1].sum;
  t[x].ans = max(t[x<<1].ans, t[x<<1|1].ans);
  t[x].lmx = max(t[x<<1].lmx, t[x<<1|1].lmx + t[x<<1].sum);
  t[x].rmx = max(t[x<<1|1].rmx, t[x<<1].rmx + t[x<<1|1].sum);
  ckmx(t[x].ans, t[x<<1].rmx + t[x<<1|1].lmx);
}
void build(int x=1,int lp=0,int rp=n-1) {
  if (lp == rp) {
    t[x].sum = val[lp];
    t[x].lmx = t[x].rmx = t[x].ans = max(0ll, val[lp]);
    return;
  }
  int mid = (lp + rp) >> 1;
  build(x << 1, lp, mid);
  build(x << 1 | 1, mid+1, rp);
  push_up(x);
}
void modify(int p,ll v,int x=1,int lp=0,int rp=n-1) {
  if (lp == rp) {
    val[p] += v;
    t[x].sum = val[lp];
    t[x].lmx = t[x].rmx = t[x].ans = max(0ll, val[lp]);
    return;
  }
  int mid = (lp + rp) >> 1;
  if (p <= mid) modify(p, v, x<<1, lp, mid);
  else modify(p, v, x<<1|1, mid+1, rp);
  push_up(x);
}
int main() {
  arr[2] = 1;
  rep (i, 3, 2 * rb)
    arr[i] = (0ll + arr[i-1] + arr[i-2] + arr[i-3]) % n;
  rep (i, 1, lb-1)
    val[arr[2 * i - 2]] += 2ll * arr[2 * i - 1] - n + 1;
  build();
  ll ans = 0;
  rep (i, lb, rb) {
    modify(arr[2 * i - 2], 2ll * arr[2 * i - 1] - n + 1);
    ans += t[1].ans;
  }
  printf("%lld\n", ans);
  return 0;
}
