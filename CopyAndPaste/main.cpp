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

#define LARGE 200
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
char S[LARGE];
set<pair<int, string>> sv[LARGE];

int solve() {
  string ss(S);
  int N = ss.length();
  for (int i = 0; i <= N; ++i) sv[i].clear();
  sv[0].insert({0, ""});
  // dynamic program
  for (int i = 1; i <= N; ++i) {
    //debug("count %d\n", i);
    int mx = INT_MAX;
    for (int j = 0; j < i; ++j) {
      //debug("sub count %d\n", j);
      for (auto& pv: sv[j]) {
        //debug("cur pv: (%d, %s)\n", pv.first, pv.second.c_str());
        //debug("substr(%d, %d): %s\n", 0, j, ss.substr(0, j).c_str());
        //debug("substr(%d, %d): %s\n", j, i, ss.substr(j, i - j).c_str());
        // count add
        if (i - j == 1) {
          mx = min(mx, pv.first + 1);
          sv[i].insert({pv.first + 1, pv.second});
          //debug("Add set\n");
        }
        // count paste
        if (ss.substr(j, i - j) == pv.second) {
          mx = min(mx, pv.first + 1);
          sv[i].insert({pv.first + 1, pv.second});
          //debug("Paset set\n");
        }
        // count copy
        if (1 < i - j && ss.substr(0, j).find(ss.substr(j, i - j)) != -1) {
          mx = min(mx, pv.first + 2);
          sv[i].insert({pv.first + 2, ss.substr(j, i - j)});
          //debug("Copy set\n");
        }
      }
    }
    // compress sv[i]
    //debug("mx: %d\n", mx);
    decltype(sv[i]) ns(sv[i]);
    for (auto nv: ns) if (mx + 1 < nv.first) sv[i].erase(nv);
  }
  // reduce answer
  int mx = INT_MAX;
  for (auto& pv: sv[N]) mx = min(mx, pv.first);
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
    scanf("%s", &S);
    int r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, r);
  }
  return 0;
}

