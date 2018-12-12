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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pri;
typedef pair<ll,ll> prl;
typedef tuple<int,int,int> tpi;
typedef vector<pri> vpri;

#define PR(x) cerr << #x << ": " << x << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)

#define LARGE 1000001
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0, N, V1, H1, A, B, C, D, E, F, M;
prl ini[LARGE];
ll cnt[4][LARGE];
ll cm[LARGE];

ll cnt_rank(int k) {
  ll res = 0;
  for (; k > 0; k -= (k & -k)) res += cm[k];
  return res;
}

ll search(int l, int r) {
  return cnt_rank(r) - cnt_rank(l - 1);
}

void update(int k) {
  for (; k < LARGE; k += (k & -k)) cm[k]++;
}

void setup() {
  memset(cm, 0, sizeof cm);
  for (int i = 1; i <= N;) {
    int c = i;
    while (i <= N && ini[i].first == ini[c].first) ++i;
    for (int j = c; j < i; ++j) {
      ll cl = ini[j].second;
      cnt[0][j] = search(1, cl - 1);
      cnt[1][j] = search(cl + 1, LARGE - 1);
    }
    for (int j = c; j < i; ++j) {
      ll cl = ini[j].second;
      update(cl);
    }
  }
  memset(cm, 0, sizeof cm);
  for (int i = N; 0 < i;) {
    int c = i;
    while (0 < i && ini[i].first == ini[c].first) --i;
    for (int j = i + 1; j <= c; ++j) {
      ll cl = ini[j].second;
      cnt[2][j] = search(1, cl - 1);
      cnt[3][j] = search(cl + 1, LARGE - 1);
    }
    for (int j = i + 1; j <= c; ++j) {
      ll cl = ini[j].second;
      update(cl);
    }
  }
}

ll count() {
  ll res = (long long)N * (N - 1) * (N - 2) / 6;
  for (int i = 1; i <= N; i++) {
    res -= cnt[0][i] * cnt[3][i] + cnt[1][i] * cnt[2][i];
  }
  return res;
}

int main(int argc, char** argv) {
  char* def_ifn = "large.in";
  char* def_ofn = "large.out";
  if (1 < argc) def_ifn = argv[1];
  if (2 < argc) def_ofn = argv[2];
  freopen(def_ifn, "r", stdin);
  freopen(def_ofn, "w", stdout);
  scanf("%d", &T);
  if (COMPILE) printf("Get T: %d\n", T);
  int i = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) cerr << "Within Case " << i << " .\n";
    cin >> N >> V1 >> H1 >> A >> B >> C >> D >> E >> F >> M;
    ini[1] = {V1, H1};
    for (int j = 2; j <= N; j++) {
      ini[j].first = (A * ini[j - 1].first + B * ini[j - 1].second + C) % M;
      ini[j].second = (D * ini[j - 1].first + E * ini[j - 1].second + F) % M;
    }
    for (int j = 1; j <= N; j++) {
      ini[j].first ++;
      ini[j].second ++;
    }
    sort(ini + 1, ini + N + 1);
    memset(cnt, 0, sizeof cnt);
    setup();
    ll res = count();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, res);
  }
  return 0;
}

