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

#define LARGE 20
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0, N = 0;
int A[LARGE][LARGE];
bool cs[LARGE];
vi path;
ll res;
int sum;

bool check() {
  //PRV(path);
  if (path.size() < 3) return false;
  int mx = *max_element(path.begin(), path.end());
  if (sum <= (mx << 1)) return false;
  return true;
}

void solve() {
  int cur = 1;
  while (cur <= N && cs[cur]) ++cur;
  if (N < cur) return;
  //PR(cur);
  cs[cur] = true;
  for (int i = 1; i <= N; ++i) {
    if (!cs[i] && 0 < A[cur][i]) {
      path.pb(A[cur][i]);
      sum += A[cur][i];
      if (check()) ++res;
      cs[i] = true;
      solve();
      cs[i] = false;
      path.pop_back();
      sum -= A[cur][i];
    }
  }
  solve();
  cs[cur] = false;
}

int main(int argc, char** argv) {
  clock_t st = clock();
  int k = 0;
  int d = 2;
  for (int i = 0; i < 1000000; ++i)
    for (int j = 0; j < 1000; ++j) k <<= 1;
  clock_t rt = clock();
  cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
  return 0;
}

