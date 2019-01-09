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
#include <unordered_set>
#include <climits>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pri;
typedef pair<ll,ll> prl;
typedef tuple<int,int,int> tpi;
typedef tuple<ll,ll,ll> tpl;
typedef vector<int> vi;
typedef vector<pri> vpri;

#define PR(x) cerr << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 1; x##_it <= (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)

#define LARGE 100005
#define COMPILE false
#define TESTTIME true
#define SMALL 5
#define TH 20

// define initial parameters here
int T = 0;
int N, K;
ll P[LARGE], H[LARGE], X[LARGE], Y[LARGE];
ll A[SMALL], B[SMALL], C[SMALL], M[SMALL];
map<ll, ll> com;

bool check_in(ld x, ld y, ld lx, ld cx, ld rx) {
  if (lx < x && x <= cx) return (y < (x - lx));
  if (cx < x && x < rx) return (y < (rx - x));
  return false;
}

prl interset(ld x1, ld y1, ld x2, ld y2) {
  ld b1 = y1 - x1;
  ld b2 = y2 + x2;
  return {(ll)(b2 - b1), (ll)(b2 + b1)};
}

void build_map() {
  com.clear();
  for (int i = 1; i <= N; ++i) {
    // insert_line(P[i] - H[i], P[i], false);
    ll clx = P[i] - H[i], crx = P[i] + H[i];
    //PR(P[i]);
    //PR(H[i]);
    //PR(clx);
    //PR(crx);
    auto lit = com.upper_bound(clx << 1);
    auto llit = com.end();
    auto rit = com.end();
    auto rrit = com.end();
    if (lit == com.end()) {
      //PR(P[i] << 1);
      //PR(H[i] << 1);
      //PR(clx << 1);
      //PR(crx << 1);
      com.insert({clx << 1, 0});
      com.insert({P[i] << 1, H[i] << 1});
      com.insert({crx << 1, 0});
    } else {
      bool has_in = false;
      for (auto jit = lit; jit != com.end(); ++jit) {
        ll x = (*jit).first, y = (*jit).second;
        if ((crx << 1) <= x) break;
        if (check_in(x, y, clx << 1, P[i] << 1, crx << 1)) {
          lit = jit;
          if (lit != com.begin()) {
            llit = --jit;
          }
          has_in = true;
          break;
        }
      }
      //PR(has_in);
      if (has_in) {
        auto tmp = lit;
        rit = tmp;
        rrit = ++tmp;
        for (; rrit != com.end(); ++rit, ++rrit) {
          ll x = (*rrit).first, y = (*rrit).second;
          if (!check_in(x, y, clx << 1, P[i] << 1, crx << 1)) break;
        }
        // process [llit, lit]
        vector<prl> v;
        if (llit != com.end()) {
          ll y = (*llit).second;
          //PR(y);
          if (y != 0) {
            prl its = interset(clx, 0, (ld)((*lit).first) / 2, (ld)((*lit).second) / 2);
            //PR(its.first);
            //PR(its.second);
            v.pb(its);
          } else {
            //PR(clx);
            //R(0);
            v.pb({clx << 1, 0});
          }
        } else {
          //PR(clx);
          //PR(0);
          v.pb({clx << 1, 0});
        }
        // push back tower point
        v.pb({P[i] << 1, H[i] << 1});
        // process [rit, rrit]
        if (rrit != com.end()) {
          ll y = (*rrit).second;
          //PR(y);
          if (y != 0) {
            prl its = interset((ld)((*rit).first) / 2, (ld)((*rit).second) / 2, crx, 0);
            //PR(its.first);
            //PR(its.second);
            v.pb(its);
          } else {
            //PR(crx);
            //PR(0);
            v.pb({crx << 1, 0});
          }
        } else {
          //PR(crx);
          //PR(0);
          v.pb({crx << 1, 0});
        }
        // delete [lit, rrit)
        com.erase(lit, rrit);
        for (auto it: v) { 
          com.insert(it);
        }
      } else {
        if (lit == com.begin()) {
          com.insert({clx << 1, 0});
          com.insert({P[i] << 1, H[i] << 1});
          com.insert({crx << 1, 0});
        } else {
          auto cit = lit;
          --lit;
          if ((*lit).second == 0 && (*cit).second == 0) {
            com.insert({clx << 1, 0});
            com.insert({P[i] << 1, H[i] << 1});
            com.insert({crx << 1, 0});
          }
        }
      }
    }
  }
}

bool below(ll cx, ll cy, ll lx, ll ly, ll rx, ll ry) {
  if (ly < ry) {
    return (lx <= cx && cy <= ly + cx - lx);
  } else if (ry < ly) {
    return (cx <= rx && cy <= ry + rx - cx);
  } else {
    return false;
  }
}

ll solve() {
  int cnt = 0;
  for (int i = 1; i <= K; ++i) {
    auto lit = com.upper_bound(X[i] << 1);
    if (lit == com.end()) continue;
    if (lit == com.begin()) continue;
    auto rit = lit;
    --lit;
    if (below(X[i] << 1, Y[i] << 1, (*lit).first, (*lit).second, (*rit).first, (*rit).second)) ++cnt;
  }
  return cnt;
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
    cin >> N >> K;
    cin >> P[1] >> P[2] >> A[1] >> B[1] >> C[1] >> M[1];
    cin >> H[1] >> H[2] >> A[2] >> B[2] >> C[2] >> M[2];
    cin >> X[1] >> X[2] >> A[3] >> B[3] >> C[3] >> M[3];
    cin >> Y[1] >> Y[2] >> A[4] >> B[4] >> C[4] >> M[4];
    for (int j = 3; j <= N; ++j) {
      P[j] = (A[1] * P[j - 1] + B[1] * P[j - 2] + C[1]) % M[1] + 1;
      H[j] = (A[2] * H[j - 1] + B[2] * H[j - 2] + C[2]) % M[2] + 1;
    }
    //PRA(P, N);
    //PRA(H, N);
    for (int j = 3; j <= K; ++j) {
      X[j] = (A[3] * X[j - 1] + B[3] * X[j - 2] + C[3]) % M[3] + 1;
      Y[j] = (A[4] * Y[j - 1] + B[4] * Y[j - 2] + C[4]) % M[4] + 1;
    }
    // build map
    build_map();
    for (auto it: com) {
      if (it.second < 0) {
        PR(it.first);
        PR(it.second);
      }
    }
    //PRA(X, K);
    //PRA(Y, K);
    // solve
    ll res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, res);
  }
  return 0;
}

