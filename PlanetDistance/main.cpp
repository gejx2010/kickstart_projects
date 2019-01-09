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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pri;
typedef tuple<int,int,int> tpi;
typedef vector<int> vi;
typedef vector<pri> vpri;

#define PR(x) cerr << #x << ": " << x << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)

#define LARGE 1001
#define COMPILE true
#define TESTTIME false

// define initial parameters here
int T = 0, N = 0;
vi C;
vi G[LARGE];
set<int> S;
set<int> Cir;
set<pri> hs;
int D[LARGE];

bool find_circle(int st) {
  // if st in set s, tell circle
  if (S.count(st)) {
    for (int i = 0; i < C.size(); ++i) 
      if (C[i] == st) {
        while (i < C.size()) 
          Cir.insert(C[i++]); 
      }
    return true;
  }
  S.insert(st);
  C.pb(st);
  for (auto it: G[st]) {
    pri v = mp(min(st, it), max(st, it));
    if (!hs.count(v)) {
      hs.insert(v);
      if (find_circle(it)) return true;
      hs.erase(v);
    }
  }
  S.erase(st);
  C.pop_back();
  return false;
}

void tell_distance() {
  set<int> nb;
  for (int i = 1; i <= N; ++i) {
    if (Cir.count(i)) {
      D[i] = 0;
    } else {
      nb.insert(i);
    }
  }
  int dis = 1;
  while (!nb.empty()) {
    // get new nabour
    set<int> nn;
    for (auto& i: nb) {
      for (auto& j: G[i]) {
        if (Cir.count(j)) { nn.insert(i); break; }
      }
    }
    for (auto& i: nn) {
      D[i] = dis;
      Cir.insert(i);
      nb.erase(i);
    }
    ++dis;
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
  int i = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) cerr << "Within Case " << i << ".\n";
    // init
    for (int j = 0; j < LARGE; ++j) G[j].clear();
    scanf("%d", &N);
    int j = 0, x, y;
    while (j++ < N) {
      scanf("%d %d", &x, &y);
      G[x].pb(y);
      G[y].pb(x);
    }
    // find circle
    S.clear();
    C.clear();
    Cir.clear();
    hs.clear();
    find_circle(1);
    if (COMPILE) {
      PRV(Cir);
    }
    // disjktra algorithm
    tell_distance();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d:", i);
    for (int j = 1; j <= N; ++j) 
      printf(" %d", D[j]);
    printf("\n");
  }
  return 0;
}

