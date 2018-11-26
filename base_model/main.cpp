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

#define PR(x) cerr << #x << ": " << x << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back

using namespace std;

#define LARGE 200001
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0;
int ini_array[LARGE], sum_array[LARGE];

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
  vector<int> n = {1, 2, 3};
  PRV(n);
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) printf("With Case %d.\n", i);
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    printf("Case #%d: \n", i);
  }
  return 0;
}

