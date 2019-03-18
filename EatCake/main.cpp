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

#define LARGE 200001
#define COMPILE false
#define TESTTIME false
#define EPSILON 1e-7

// define initial parameters here
int T = 0, N;
int ini[LARGE], sum[LARGE];

int solve() {
  int i = (int)sqrt((double)N + EPSILON);
  int mx = 10;
  while (0 < i) {
    int li = N - i * i;
    if (li < 0) { --i; continue; }
    if (li == 0) return 1;
    int j = (int)sqrt((double)li + EPSILON);
    while (i < j) --j;
    while (0 < j) {
      int lj = li - j * j;
      if (lj == 0) { mx = min(mx, 2); break; }
      int k = (int)sqrt((double)lj + EPSILON);
      while (j < k) --k;
      while (0 < k) {
        int lk = lj - k * k;
        if (lk == 0) { mx = min(mx, 3); break; }
        int m = (int)sqrt((double)lk + EPSILON);
        if (k < m) break;
        if (m * m == lk) { mx = min(mx, 4); }
        --k;
      }
      --j;
    }
    --i;
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
    scanf("%d", &N);
    int res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}

