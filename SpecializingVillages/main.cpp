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

#define PR(x) cout << #x << ": " << (x) << endl;
#define PRA(x,sz) cout << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cout << (x)[x##_it] << " "; cout << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)

#define LARGE 100
#define ELARGE 2500
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0, V = 0, E = 0;
tpi edge[ELARGE];
vi nbr[LARGE];
set<int> hs;
bool color[LARGE];
ll path_len[LARGE];
ll min_dis;
ll cnt_min;
ll cur_dis;

void sub_select(int np, int cp, int rk, int len);
void select(int rk);
void solve();

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
    scanf("%d %d", &V, &E);
    int cp, np, len;
    for (int i = 0; i < LARGE; ++i) nbr[i].clear();
    for (int j = 0; j < E; ++j) {
      scanf("%d %d %d", &cp, &np, &len);
      edge[j] = mt(len, cp, np);
      nbr[cp].pb(np);
      nbr[np].pb(cp);
    }
    // sort length for edge
    sort(edge, edge + E);
    solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, cnt_min);
  }
  return 0;
}

void sub_select(int np, int cp, int rk, int len) {
  if (path_len[cp] == 0) {
    color[np] = 0;
    hs.insert(np);
    cur_dis += len;
    path_len[np] = len;
    select(rk + 1);
    cnt_min <<= 1;
    path_len[np] = 0;
    hs.erase(np);
    cur_dis -= len;
  } else {
    color[np] = !color[cp];
    hs.insert(np);
    cur_dis += len;
    path_len[np] = len;
    select(rk + 1);
    hs.erase(np);
    cur_dis -= len;
    path_len[np] = 0;
  }
}

void select(int rk) {
  if (hs.size() == V) {
    if (cur_dis < min_dis) {
      min_dis = cur_dis;
      cnt_min = 1;
    } else if (cur_dis == min_dis) ++cnt_min;
    return;
  }
  ll a, b, len;
  tie(len, a, b) = edge[rk];
  if (hs.count(a) && hs.count(b)) return select(rk + 1); 
  else if (hs.count(a)) { // check if there is a way smaller than len
    return sub_select(b, a, rk, len);
  } else if (hs.count(b)) {
    return sub_select(a, b, rk, len);
  } else {
    color[a] = 0;
    color[b] = 1;
    hs.insert(a);
    hs.insert(b);
    cur_dis += (len << 1);
    path_len[a] = len;
    path_len[b] = len;
    select(rk + 1);
    cnt_min <<= 1;
    hs.erase(a);
    hs.erase(b);
    path_len[a] = 0;
    path_len[b] = 0;
    cur_dis -= (len << 1);
  }
}

void solve() {
  hs.clear();
  memset(color, 0, sizeof color);
  memset(path_len, 0, sizeof path_len);
  cur_dis = 0;
  min_dis = LLONG_MAX;
  select(0);
}

