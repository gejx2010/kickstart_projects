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
typedef pair<ll,ll> prl;
typedef tuple<int,int,int> tpi;
typedef tuple<ll,ll,ll> tpl;
typedef vector<int> vi;
typedef vector<pri> vpri;

#define PR(x) cout << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 1; x##_it <= (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)
#define num(x) ((x) - 'A')

#define LARGE 101
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0, R, C, W;
char ini[LARGE][LARGE];
string word[1001];
ll wm, wh, times;
ll column[LARGE];
ll lleft[LARGE][LARGE][LARGE];
ll down[LARGE][LARGE][LARGE];
ll sum_left[LARGE][LARGE][LARGE];
ll sum_down[LARGE][LARGE][LARGE];
int nnext[10005][30];
int weight[10005];
int nodes;

void insert(string s, int len) {
  int id = 1;
  for (int i = len - 1; 0 <= i; --i) {
    int v = num(s[i]);
    if (nnext[id][v] == 0) nnext[id][v] = ++nodes;
    id = nnext[id][v];
  }
  weight[id] += len;
}

void precompute() {
  memset(nnext, 0, sizeof nnext);
  memset(weight, 0, sizeof weight);
  nodes = 1;
  for (int i = 0; i < W; ++i) 
    if (word[i].length() < LARGE) {
      insert(word[i], word[i].length());
      reverse(word[i].begin(), word[i].end());
      insert(word[i], word[i].length());
    }
  memset(lleft, 0, sizeof lleft);
  memset(down, 0, sizeof down);
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      // compute lleft
      int id = 1;
      lleft[i][j][0] = 0;
      for (int k = j; 0 <= k; --k) {
        id = nnext[id][num(ini[i][k])];
        lleft[i][j][j - k + 1] = lleft[i][j][j - k] + weight[id];
      }
      // compute down
      id = 1;
      down[i][j][0] = 0;
      for (int k = i; 0 <= k; --k) {
        id = nnext[id][num(ini[k][j])];
        down[i][j][i - k + 1] = down[i][j][i - k] + weight[id];
      }
    }
  }
}

ll gmd(ll a, ll b) {
  if (a < b) return gmd(b, a);
  if (a % b == 0) return b;
  return gmd(b, a % b);
}

void frac(ll a, ll b, ll& c, ll& d) {
  // irreducible a / b
  if (a == 0) return;
  ll e = gmd(a, b);
  c = a / e;
  d = b / e;
}

void solve() {
  // precalculate word position
  precompute();
  memset(sum_left, 0, sizeof sum_left);
  memset(sum_down, 0, sizeof sum_down);
  wm = 0, wh = 1, times = 0;
  // compute with lleft array
  for (int j = 0; j < C; ++j) {
    memset(column, 0, sizeof column);
    for (int k = 0; k < R; ++k) {
      for (int m = j; m < C; ++m) 
        column[m] += lleft[k][m][m - j + 1];
      ll sum = 0;
      for (int m = j; m < C; ++m) {
        sum += column[m];
        sum_left[j][k][m] = sum;
      }
    }
  }
  // compute with down array
  for (int i = 0; i < R; ++i) {
    memset(column, 0, sizeof column);
    for (int k = 0; k < C; ++k) {
      for (int m = i; m < R; ++m) 
        column[m] += down[m][k][m - i + 1];
      ll sum = 0;
      for (int m = i; m < R; ++m) {
        sum += column[m];
        sum_down[i][m][k] = sum;
      }
    }
  }
  // compute with all
  for (int i = 0; i < R; ++i) {
    // search in [i, R) for j
    for (int j = 0; j < C; ++j) {
      for (int k = i; k < R; ++k) {
        int cwh = (k - i + 2);
        for (int m = j; m < C; ++m, ++cwh) {
          ll sum = (i == 0) ? sum_left[j][k][m] : sum_left[j][k][m] - sum_left[j][i - 1][m];
          sum += (j == 0) ? sum_down[i][k][m] : sum_down[i][k][m] - sum_down[i][k][j - 1];
          //if (INT_MAX < sum * wh) PR(sum * wh);
          if (wm * cwh < sum * wh) {
            wm = sum;
            wh = cwh;
            times = 1;
          } else if (wm * cwh == sum * wh) 
            times++;
        }
      }
    }
  }
  frac(wm, wh, wm, wh);
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
    scanf("%d %d %d", &R, &C, &W);
    for (int j = 0; j < R; ++j) scanf("%s", &ini[j]);
    char s[5001];
    for (int j = 0; j < W; ++j) {
      scanf("%s", s);
      word[j] = s;
    }
    solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d/%d %d\n", i, wm, wh, times);
  }
  return 0;
}

