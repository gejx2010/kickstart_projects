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
#define mp make_pair
#define mt make_tuple
#define pb push_back

using namespace std;

#define LARGE 5000001
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0, N = 0;
char ini[LARGE];
int ini_array[LARGE];

void printf_array(void* a, int num, char* name, char* type="int") {
  printf("Begin print content of %s:\n", name);
  int* b = NULL;
  long long* c = NULL;
  if (strcmp(type, "int") == 0) b = (int*)a; 
  else c = (long long*)a;
  for (int k = 0; k < num; k++) {
    if (strcmp(type, "int") == 0) printf("%d ", b[k]);
    else printf("%lld ", c[k]);
  }
  printf("\nAfter print content of %s.\n", name);
}
#define PRA(a, num, name, type) printf_array(a, num, name, type)

bool allow(int st, int ed) {
  int right = min(st << 1, ed);
  int left = max((ed << 1) + 1 - N, st);
  return (left <= right);
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
    if (TESTTIME) printf("With Case %d.\n", i);
    scanf("%d", &N);
    scanf("%s", ini);
    int res = 0;
    int sum = 0;
    int n = (N + 1) / 2;
    for (int j = 0; j < n; j++) {
      sum += ini[j] - '0';
      if (allow(0, n - 1)) res = sum;
    }
    for (int j = n; j < N; j++) {
      sum += ini[j] - '0';
      sum -= ini[j - n] - '0';
      if (allow(j - n + 1, j) & res < sum) res = sum;
    }
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    if (COMPILE) printf_array(ini_array, 0, "ini_array", "int");
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}
