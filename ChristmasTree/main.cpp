#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <map>
#include <stack>
#include <queue>
#include <cassert>
#include <tuple>
#include <set>
#include <bitset>
#include <climits>
#include <cfloat>
#include <numeric>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pri;
typedef pair<ll,ll> prl;
typedef tuple<int,int,int> tpi;
typedef tuple<ll,ll,ll> tpl;
typedef vector<int> vi;
typedef set<int> si;
typedef vector<pri> vpri;
typedef vector<pri> vtpi;

using prd = pair<double,double>;

#define PR(x) cout << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stdout, __VA_ARGS__)
#define rep(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)

#define LARGE 105
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
int N, M, K;
char S[LARGE][LARGE];
int DP[LARGE][LARGE];
int OK[LARGE][LARGE][LARGE];
int MK[LARGE][LARGE][LARGE][LARGE];

bool istree(int i, int j) {
  return S[i][j] == '#';
}

int visit(int x, int y) {
  int mh = min(N + 1 - x, min(y, M - y + 1));
  inc (i, 0, mh) {
    inc (j, y - i, y + i + 1) {
      if (!istree(x + i, j)) return i * i;
    }
  }
  return mh * mh;
}

int ccd(int n) {
  return (n + 1) * (n + 1) - n * n;
}

int omax(int a, int b, int c) {
  return max(a, max(b, c));
}

int solve() {
  memset(DP, 0, sizeof DP);
  memset(MK, 0, sizeof MK);
  memset(OK, 0, sizeof OK);
  int mx = 0;
  dec (i, N, 1) dec (j, M, 1) {
    if (istree(i, j)) 
      DP[i][j] = min(min(DP[i + 1][j - 1], DP[i + 1][j]), DP[i + 1][j + 1]) + 1;
    mx = max(DP[i][j] * DP[i][j], mx);
  }
  //if (K == 1) return mx;
  mx = 0;
  dec (i, N, 1) dec(j, M, 1) {
    if (DP[i][j]) {
      inc (k, 1, K + 1) {
        int mvd = 0;
        inc (n, 1, N + 1) {
          if (n == 1) {
            if (OK[i + 1][j][k - 1] == 0 && k != 1) MK[i][j][k][n] = 0;
            else MK[i][j][k][n] = OK[i + 1][j][k - 1] + 1;
          } else {
            if (DP[i][j] < n) { break; }
            else {
              int cx = omax(MK[i + 1][j - 1][k][n - 1],
                                   MK[i + 1][j][k][n - 1],
                                   MK[i + 1][j + 1][k][n - 1]);
              if (cx == 0) MK[i][j][k][n] = 0;
              else MK[i][j][k][n] = cx + (2 * n - 1);
            }
          }
          //debug("MK(%d, %d, %d, %d): %d\n", i, j, k, n, MK[i][j][k][n]);
          mvd = max(mvd, MK[i][j][k][n]);
          if (k == K) mx = max(mx, MK[i][j][k][n]);
        }
        OK[i][j][k] = mvd;
      }
    }
  }
  return mx;
}

int main(int argc, char** argv) {
  string def_ifn = "large.in";
  string def_ofn = "large.out";
  if (1 < argc) def_ifn = argv[1];
  if (2 < argc) def_ofn = argv[2];
  freopen(def_ifn.c_str(), "r", stdin);
  freopen(def_ofn.c_str(), "w", stdout);
  scanf("%d", &T);
  if (COMPILE) printf("Get T: %d\n", T);
  int i = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) cerr << "Within Case " << i << ".\n";
    scanf("%d %d %d", &N, &M, &K);
    inc (j, 1, N + 1) scanf("%s", S[j] + 1);
    int res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}

