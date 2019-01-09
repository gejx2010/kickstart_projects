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
#define rep(i,a,b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)

#define LARGE 500050
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
ll N, O, D, X1, X2, A, B, C, M, L;
int S[LARGE];
ll sum[LARGE];
ll odd[LARGE];
multiset<ll> sset;

ll solve() {
  // compute sum array and odd array
  sum[0] = 0;
  odd[0] = 0;
  for (int i = 1; i <= N; ++i) {
    sum[i] = sum[i - 1] + S[i];
    odd[i] = odd[i - 1] + (S[i] & 1);
  }
  // compute max sum
  ll res = LLONG_MIN;
  ll cs = 0;
  ll co = 0;
  int st = 1; // book for last odd
  sset.clear();
  for (int i = 1; i <= N; ++i) {
    co += (S[i] & 1);
    sset.insert(sum[i - 1]);
    while (O < co) {
      co -= S[st] & 1;
      auto it = sset.find(sum[st - 1]);
      auto jit = it;
      ++it;
      sset.erase(jit, it);
      ++st;
    }
    auto it = sset.lower_bound(sum[i] - D);
    if (it != sset.end()) res = max(res, sum[i] - *it);
  }
  return res;
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
    cin >> N >> O >> D;
    cin >> X1 >> X2 >> A >> B >> C >> M >> L;
    S[1] = X1 + L;
    S[2] = X2 + L;
    ll X;
    for (int i = 3; i <= N; ++i) {
      X = (A * X2 + B * X1 + C) % M;
      X1 = X2;
      X2 = X;
      S[i] = X + L;
    }
    ll res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    if (LLONG_MIN < res) printf("Case #%d: %lld\n", i, res);
    else printf("Case #%d: IMPOSSIBLE\n", i);
  }
  return 0;
}

