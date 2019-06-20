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

const int N = 55, L = 25;
string dp[N][L];
bool emp[N], mat[N][N];
int n,l,per[N];
bool isl(char c) {
  return c >= 'a' && c <= 'z';
}
string doit(string b,int lim) {
  static string tdp[L][L];
  int m = (int)b.size();
  rep (i, 0, m) rep (j, 0, lim) tdp[i][j] = "{";
  tdp[0][0] = "";
  rep (i, 1, m) rep (j, 0, lim) {
    if (isl(b[i-1])) {
      if (j > 0) ckmn(tdp[i][j], tdp[i-1][j-1] + b[i-1]);
    } else {
      int v = b[i-1] - 'A';
      if (emp[v]) ckmn(tdp[i][j], tdp[i-1][j]);
      rep (a, 1, j) if (dp[v][a][0] <= 'z')
        ckmn(tdp[i][j], tdp[i-1][j-a] + dp[v][a]);
    }
  }
  return tdp[m][lim];
}
void dfs(int pos,int len) {
  rep (i, 0, 25) if (dp[i][len] > dp[pos][len] && mat[pos][i]) {
    dp[i][len] = dp[pos][len];
    dfs(i, len);
  }
}
vector<string> tran[N];
void solve() {
  rep (i, 0, 25) tran[i].clear();
  rep (i, 1, n) {
    string tmp;
    cin >> tmp;
    tran[tmp[0] - 'A'].push_back(tmp.substr(2));
  }
  rep (i, 0, 25) rep (j, 1, l) dp[i][j] = string(j, 'z' + 1);
  rep (i, 0, 25) emp[i] = 0;
  while (true) { // l = 0, special case
    int key = 0;
    rep (i, 0, 25) if (!emp[i])
      rep (j, 0, (int)tran[i].size()-1) {
        int tmp = 1;
        rep (k, 0, (int)tran[i][j].size()-1)
          if (isl(tran[i][j][k])) tmp = 0;
          else tmp &= emp[tran[i][j][k]-'A'];
        if (tmp) key = emp[i] = 1;
      }
    if (!key) break;
  }
  memset(mat, 0, sizeof mat);
  rep (i, 0, 25) rep (j, 0, 25) {
    rep (a, 0, (int)tran[i].size()-1) {
      int vis = 0, key = 1;
      rep (k, 0, (int)tran[i][a].size()-1)
        if (isl(tran[i][a][k])) key = 0;
        else {
          int v = tran[i][a][k] - 'A';
          if (v == j && !vis) vis = 1;
          else key &= emp[v];
        }
      if (key && vis) mat[j][i] = 1;
    }
  }
  rep (a, 1, l) {
    rep (i, 0, 25) rep (j, 0, (int)tran[i].size()-1)
      ckmn(dp[i][a], doit(tran[i][j], a));
    rep (i, 0, 25) per[i] = i;
    sort(per, per+26, [=](const int& i,const int& j) -> bool {
        return dp[i][a] < dp[j][a];
      });
    rep (i, 0, 25) dfs(per[i], a);
  }
  if (l == 0) {
    if (!emp['S'-'A']) puts("-");
    else puts("");
  } else {
    if (dp['S'-'A'][l][0] > 'z') puts("-");
    else cout << dp['S'-'A'][l] << endl;
  }
}

int main() {
  while (true) {
    read(n), read(l);
    if (!n && !l) break;
    solve();
  }
  return 0;
}
