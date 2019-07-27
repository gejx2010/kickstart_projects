/***************************************
Author: spgoal
Date: Sun, May/26/2019, 18:51:03
Lang: C++
***************************************/

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
#define PRA(x,sz) cerr << #x << ": " << endl; for (int xit = 0; xit < (sz); ++(xit)) cerr << (x)[xit] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& xit: x) cerr << xit << ' '; cerr << endl;
#define PRM(x) cout << #x << ": " << endl; for (auto& xit: x) cout << (xit).first << ": " << (xit).second << endl; cout << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (decltype((b) + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype((b) + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype((a) + 0) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)
#define lch(x) ((x) << 1)
#define rch(x) (((x) << 1) + 1)

#define SMALL 51
#define LARGE 1001
#define LLARGE 100001
#define COMPILE false
#define TESTTIME false
#define MOD 1000000007

// define initial parameters here
int T = 0;
int N, K;
int P[LARGE], A[LARGE];
pri M[LARGE];
int C[LARGE][LARGE];
int CC[LARGE];
ll V[LARGE][LARGE];
ll S[LARGE][LARGE];

void init() {
  inc (i, 1, N + 1) M[i] = {P[i], A[i]};
  sort(M + 1, M + N + 1);
  inc (i, 1, LARGE) {
    int cnt = 0;
    inc (j, 1, N + 1) {
      if (M[j].second == i) {
        C[i][++cnt] = j;
      }
    }
    CC[i] = cnt;
  }
}

ll solve() {
  init();
  inc (i, 0, LARGE) {
    V[i][0] = 0;
    inc (j, 1, LARGE) {
      V[i][j] = INT_MAX;
    }
  }
  memset(S, 0, sizeof S);
  inc (i, 1, LARGE) {
    inc (k, 1, K + 1) {
      //PR(i);
      //PR(k);
      V[i][k] = V[i - 1][k];
      S[i][k] = S[i - 1][k];
      //PR(V[i][k]);
      inc (j, 1, CC[i] + 1) {
        ll ss;
        int cc;
        if (j <= k) {
          int r = C[i][j];
          int rr = S[i - 1][k - j];
          //PR(r);
          //PR(rr);
          //PR(M[r].first);
          //PR(M[rr].first);
          if (rr < r) {
            ss = V[i - 1][k - j] + M[r].first + M[rr].first;
            cc = r;
          } else {
            ss = V[i - 1][k - j] + 2 * M[r].first;
            cc = rr;
          }
          if (ss < V[i][k]) {
            V[i][k] = ss;
            S[i][k] = cc;
          }
          //PR(j);
          //PR(V[i][k]);
        }
      }
    }
  }
  return V[LARGE - 1][K];
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
    inc (j, 1, N + 1) cin >> P[j];
    inc (j, 1, N + 1) cin >> A[j];
    ll r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, r);
  }
  return 0;
}

