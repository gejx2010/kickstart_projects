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
typedef vector<tpi> vtpi;

#define PR(x) cerr << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)

#define LARGE 200
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0;
int N, M;
char ini[LARGE][LARGE];
vector<tuple<char,int,int>> vp;

enum ST {
  INI = 0,
  ADD = 1,
  XXX = 2,
  OOO = 3
};

char dec[] = { '0', '+', 'x', 'o'};

bool is_clt(int r, int l) {
  return row_clt(r) || col_clt(l) || dia_clt(r, l);
}
bool fill_one_st(int r, int l, ST st) {
  if (ini[r][l] == 'o') return false;
  if (st == OOO) {
    if (is_clt(r,l)) return false;
    return true;
  }
  if (ini[r][l] == 0 && 0 < st) {
    if (is_clt(r,l)) return false;
    return true;
  }
  if (0 < ini[r][l]) return false;
  return false;
}

bool fill_one(int r, int l) {
  if (N < l) return true;
  bool can_fill = false;
  for (int i = 3; 0 < i; --i) 
    if (fill_one_st(r, l, i)) {
      vp.pb(mt(dec[i], r, l));
      char bef = in[r][l];
      ini[r][l] = dec[i];
      if (fill_one(r, l + 1)) {
        can_fill = true;
      }
      ini[r][l] = bef;
      vp.pop_back();
      if (can_fill) return true;
    }
  return false;
}

void fill_row(int r) {
  if (N < r) return;
  bool ow = false;
  fill_one(r, i);`
}

void solve() {
  vp.clear();
  fill_row(1);
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
    scanf("%D, %d", &N, &M);
    char c;
    int row, col;
    for (int j = 0; j < M; ++j) {
      scanf("%c %d %d", &c, &row, &col);
      ini[row][col] = c;
    }
    solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: \n", i);
  }
  return 0;
}

