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
#include <climits>
#include <numeric>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pri;
typedef pair<ll,ll> prl;
typedef tuple<int,int,int> tpi;
typedef tuple<ll,ll,ll> tpl;
typedef vector<int> vi;
typedef vector<pri> vpri;
typedef vector<pri> vtpi;

#define PR(x) cerr << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)

#define LARGE 50
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0;
int R, C;
char S[LARGE][LARGE];
int mark[LARGE];

void solve() {
  memset(mark, 0, sizeof mark);
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      PR(i);
      PR(j);
      PR(S[i][j]);
      if (S[i][j] != '?' && !mark[S[i][j] - 'A']) {
        mark[S[i][j] - 'A'] = true;
        int n = 1, l = -1, r = -1, k = 0;
        for (k = j - 1; 0 <= k; --k, ++n) {
          if (S[i][k] == '?') S[i][k] = S[i][j];
          else break;
        }
        l = k + 1;
        for (k = j + 1; k < C; ++k, ++n) {
          if (S[i][k] == '?') S[i][k] = S[i][j];
          else break;
        }
        r = k - 1;
        int cft = false;
        for (k = i - 1; 0 <= i && !cft; --k) {
          for (int m = l; m <= r; ++m) {
            if (S[k][m] != '?') {
              cft = true;
              break;
            }
          }
          if (!cft) {
            for (int m = l; m <= r; ++m) {
              S[k][m] = S[i][j];
            }
          }
        }
        cft = false;
        PR(S[i][j]);
        for (k = i + 1; k < R && !cft; ++k) {
          for (int m = l; m <= r; ++m) {
            PR(k);
            PR(m);
            PR(S[k][m]);
            if (S[k][m] != '?') {
              cft = true;
              break;
            }
          }
          if (!cft) {
            for (int m = l; m <= r; ++m) {
              S[k][m] = S[i][j];
            }
          }
        }
      }
    }
  }
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
    scanf("%d %d", &R, &C);
    for (int j = 0; j < R; ++j) scanf("%s", &S[j]);
    solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d:\n", i);
    for (int j = 0; j < R; ++j) printf("%s\n", S[j]);
  }
  return 0;
}

