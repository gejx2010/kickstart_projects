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

#define LARGE 200001
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0;
ll Hd, Ad, Hk, Ak, B, D;

//ll solve() {
//  // if only one turn, return directly
//  if (Hk <= Ad) return 1;
//  // 1 < hm
//  ll hm = 0;
//  if (B == 0) {
//    hm = ceil((ld)Hk / Ad);
//  } else {
//    hm = sqrt((ld) Hk / B) - (ld) A / B;
//  }
//  ll dm = LLONG_MAX;
//  if (D == 0) {
//    ll tm = ceil((ld) Hd / Ak) - 1;
//    if (tm <= 0) return -1;
//    dm = ceil((ld)hm / tm);
//    return hm + dm;
//  } else {
//    ll dt = 0;
//    ll tt = 0;
//    bool bfo = true;
//    ll hh = Hd, kk = Ak;
//    bool cando = false;
//    while (true) {
//      ll tm = ceil((ld) Hd / kk) - 1;
//      if (tm <= 0) {
//        tt = -1;
//        bfo = false;
//      } else {
//        cando = true;
//        ll ndm = (tt == 0) ? ceil((ld) hm / tm) + tt : ceil((ld) (hm + 1) / tm) + tt;
//        if (ndm < dm) dm = ndm;
//        else {
//          tt = dm;
//          break;
//        }
//      }
//      // do debuff
//      kk -= D;
//      hh -= kk;
//      ++dt;
//      ++tt;
//      if (hh <= 0) break;
//      if (hh <= kk) {
//        // do cure
//        ++tt;
//        hh = Hd - kk;
//        if (hh <= kk) break;
//      }
//    }
//    return hm + tt;
//  }
//}
//

ll find_min(ll hd, ll ad, ll hk, ll ak) {
  // Attack
  if (hk <= ad) return 1;
  // Cure
  if (hd <= ak && hd != Hd) {
    hd = Hd - ak;
    return find_min(hd, ad, hk, ak) + 1;
  }
  // Debuff
  
  // Buff
}

ll solve() {
  return find_min(Hd, Ad, Hk, Ak);
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
    cin >> Hd >> Ad >> Hk >> Ak >> B >> D;
    ll res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    if (0 <= res) printf("Case #%d: %lld\n", i, res);
    else printf("Case #%d: IMPOSSIBLE\n", i, res);
  }
  return 0;
}

