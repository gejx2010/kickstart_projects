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
ll N, X, K, A, B, C;

map<ll, ld> m;
map<ll, ld> bm;

ld cmp_bm() {
  ld r = 0.0;
  for (auto v: bm) {
    ld c = v.second * v.first;
    r += c;
  }
  return r;
}

ld cmp_m() {
  ld r = 0.0;
  for (auto v: m) r += v.second * v.first; 
  return r;
}

void try_insert(map<ll, ld>& m, ll v, ld p) {
  if (m.count(v)) m[v] += p;
  else m[v] = p;
}

ld solve() {
  // init
  bm.clear();
  ld a = (ld) A / 100.0;
  ld b = (ld) B / 100.0;
  ld c = (ld) C / 100.0;
 
  try_insert(bm, X & K, a);
  try_insert(bm, X | K, b);
  try_insert(bm, X ^ K, c);
  if (N == 1) return cmp_bm();
  // larger map
  inc (i, 2, N + 1) {
    m.clear();
    for (auto v: bm) {
      ll n = v.first;
      ld p = v.second;
      try_insert(m, n & K, p * a);
      try_insert(m, n | K, p * b);
      try_insert(m, n ^ K, p * c);
    }
    bm = m;
  }
  return cmp_m();
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
    cin >> N >> X >> K >> A >> B >> C;
    ld r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %.10llf\n", i, r);
  }
  return 0;
}

