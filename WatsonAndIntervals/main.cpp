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

#define PR(x) cout << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stdout, __VA_ARGS__)
#define rep(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)

#define LARGE 500001
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
ll N, L1, R1, A, B, C1, C2, M;
ll L[LARGE], R[LARGE];
prl Q[LARGE];
multimap<ll, prl> S;

ll sweep_line() {
  set<ll> s;
  ll cl = 0, bf = 0, hf = 0;
  ll cm = 0, cr = 0;
  for (auto p: S) {
    ll x = p.first;
    auto vp = p.second;
    ll f = vp.first, k = vp.second;
    //debug("x, f, k: (%d, %d, %d)\n", x, f, k);
    if (s.empty()) {
      s.insert(k);
      cl = 1;
      hf += 1;
      cr = k;
    } else if (s.size() == 1) {
      hf += (x - bf);
      if (f == 0) {
        cl += (x - bf - 1); 
        s.insert(k);
      } else {
        cl += (x - bf);
        s.erase(k);
        cm = max(cm, cl);
        cl = 0;
      }
    } else {
      hf += (x - bf);
      if (f == 0) {
        s.insert(k);
      } else {
        if (cr == k) {
          cm = max(cm, cl);
          cl = 0;
        }
        s.erase(k);
        if (s.size() == 1) cr = *s.begin();
      }
    }
    bf = x;
    //PR(cm);
  }
  //PR(hf);
  //PR(cm);
  return hf - cm;
}

ll solve() {
  S.clear();
  inc (i, 1, N + 1) Q[i] = {L[i], R[i]};
  sort(Q + 1, Q + N + 1);
  inc (i, 1, N + 1) {
    S.insert(mp(Q[i].first, mp(0, i)));
    S.insert(mp(Q[i].second, mp(1, i)));
  }
  return sweep_line();
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
    cin >> N >> L1 >> R1 >> A >> B >> C1 >> C2 >> M;
    L[1] = L1, R[1] = R1;
    ll x, y, xx = L1, yy = R1;
    inc (j, 2, N + 1) {
      x = (A * xx + B * yy + C1) % M;
      y = (A * yy + B * xx + C2) % M;
      xx = x, yy = y;
      L[j] = min(x, y), R[j] = max(x, y);
    }
    //inc (j, 1, N + 1) 
      //debug("pair %lld: (%lld, %lld)\n", j, L[j], R[j]);
    ll res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, res);
  }
  return 0;
}

