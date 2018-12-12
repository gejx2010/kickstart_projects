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
typedef tuple<int,int,int> tpi;
typedef vector<pri> vpri;

#define PR(x) cerr << #x << ": " << x << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define LARGE 201
#define COMM 1<<16
#define COMPILE false
#define TESTTIME false
#define gel(x, i) get<(i)>((x))

// define initial parameters here
int T = 0, N = 0, K = 0;
long long P = 0;
vpri rmap[LARGE];
long double num[LARGE][COMM];
bool done[LARGE][COMM];

long double gen(int a, int b) {
  if (done[a][b]) return num[a][b];
  done[a][b] = true;
  for (auto& it: rmap[a]) {
    if (__builtin_popcount(b >> (15 - a + it.first)) != it.second) {
      return num[a][b] = 0;
    }
  }
  if (a == N) return num[a][b] = 1;
  return num[a][b] = gen(a + 1, b >> 1) + gen(a + 1, (b >> 1) + (1 << 15));
}

string count_set() {
  string res;
  int b = 0;
  for (int i = 0; i < N; i++) {
    if (P <= gen(i + 1, b >> 1)) {
      res += '0';
      b >>= 1;
    } else {
      res += '1';
      P -= gen(i + 1, b >> 1);
      b = (b >> 1) + (1 << 15);
    }
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
    scanf("%d %d %lld", &N, &K, &P);
    int a, b, c;
    for (int j = 0; j < LARGE; j++) rmap[j].clear();
    memset(done, 0, sizeof done);
    for (int j = 0; j < K; j++) {
      scanf("%d %d %d", &a, &b, &c);
      rmap[b].pb({a, c});
    }
    // count K
    string res = count_set();
    if (TESTTIME) printf("With Case %d.\n", i);
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    printf("Case #%d: %s\n", i, res.c_str());
  }
  return 0;
}

