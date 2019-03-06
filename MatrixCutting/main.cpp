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
#define TESTTIME true

// define initial parameters here
int T = 0;
int N, M;
int ini[LARGE][LARGE], sum[LARGE][LARGE][LARGE][LARGE], ma[LARGE][LARGE][LARGE][LARGE];
bool mark[LARGE][LARGE][LARGE][LARGE];
bool mark_min[LARGE][LARGE][LARGE][LARGE];

int min_arr(int lu, int ru, int ld, int rd) {
  if (mark_min[lu][ru][ld][rd]) return ma[lu][ru][ld][rd];
  if (ld - lu < 1) {
    if (rd - ru < 1) ma[lu][ru][ld][rd] = ini[lu][ru];
    else ma[lu][ru][ld][rd] = min(min_arr(lu, ru, ld, rd - 1), ini[lu][rd]);
  } else 
      ma[lu][ru][ld][rd] = min(min_arr(lu, ru, ld - 1, rd), min_arr(ld, ru, ld, rd));
  mark_min[lu][ru][ld][rd] = true;
  //debug("min (%d, %d, %d, %d), RES: %d\n", lu, ru, ld, rd, ma[lu][ru][ld][rd]);
  return ma[lu][ru][ld][rd];
}

int cut(int lu, int ru, int ld, int rd) {
  if (mark[lu][ru][ld][rd]) return sum[lu][ru][ld][rd];
  int s = 0;
  for (int i = lu; i < ld; ++i) {
    int cur_sum = cut(lu, ru, i, rd) + cut(i + 1, ru, ld, rd) + min_arr(lu, ru, ld, rd);
    s = max(s, cur_sum);
  }
  for (int i = ru; i < rd; ++i) {
    int cur_sum = cut(lu, ru, ld, i) + cut(lu, i + 1, ld, rd) + min_arr(lu, ru, ld, rd);
    s = max(s, cur_sum);
  }
  //debug("cut %d, %d, %d, %d, RES: %d\n", lu, ru, ld, rd, s);
  mark[lu][ru][ld][rd] = true;
  sum[lu][ru][ld][rd] = s;
  return s;
}

int solve() {
  memset(mark, 0, sizeof mark);
  memset(mark_min, 0, sizeof mark_min);
  return cut(1, 1, N, M);
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
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; ++i) 
      for (int j = 1; j <= M; ++j) 
        scanf("%d", &ini[i][j]);
    int res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}

