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

#define PR(x) cerr << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)

#define LARGE 200001
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0;
int N;
char SL[LARGE];
char SM[LARGE];

bool track_pace(pri il, pri im, int cnt, char dir) {
  if (cnt == (N << 1) - 2) { SM[cnt] = '\0'; return true; }
  int x = im.first, y = im.second;
  if (dir == 'E' && x == N) return false;
  if (dir == 'S' && y == N) return false;
  if (il == im && dir == SL[cnt]) return false;
  if (dir == 'E') {
    im = {x + 1, y};
    SM[cnt] = 'E';
  } else {
    im = {x, y + 1};
    SM[cnt] = 'S';
  }
  if (SL[cnt] == 'E') il = {il.first + 1, il.second};
  else il = {il.first, il.second + 1};
  ++cnt;
  if (track_pace(il, im, cnt, 'E')) return true;
  return track_pace(il, im, cnt, 'S');
}

void solve() {
  inc (i, 0, 2 * N - 2) {
    if (SL[i] == 'E') SM[i] = 'S';
    else SM[i] = 'E';
  }
  SM[2 * N - 2] = '\0';
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
    scanf("%s", SL);
    solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %s\n", i, SM);
  }
  return 0;
}

