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

#define LARGE 200001
#define MODULE 1000000007
#define COMM 200001
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0, N = 0, M = 0;
int step_array[COMM], pow_array[COMM], ini_array[LARGE], mod_one_array[LARGE];

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

int fast(int n, int k) {
  int ans = 1;
  while (k) {
    if (k & 1) ans = (long long)ans * n % MODULE;
    n = (long long)n * n % MODULE;
    k >>= 1;
  }
  return ans;
}

int count_combo(int n, int m) {
  return (long long)step_array[n] * mod_one_array[m] % MODULE * mod_one_array[n - m] % MODULE;
}

int count_way(int N, int M) {
  long long res = 0, tr = 1;
  for (int i = 0; i <= M; i++, tr *= -1) {
    long long cur = (long long)step_array[2 * N - i] * count_combo(M, i) % MODULE;
    if (tr == -1) cur = MODULE - cur;
    cur = (long long)cur * pow_array[i] % MODULE;
    res += cur;
  }
  return res % MODULE;
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
  step_array[0] = 1;
  pow_array[0] = 1;
  for (int v = 1; v < COMM; v++) {
    step_array[v] = ((long long)step_array[v - 1] * v % MODULE);
    pow_array[v] = ((long long)pow_array[v - 1] * 2 % MODULE);
  }
  mod_one_array[COMM - 1] = fast(step_array[COMM - 1], MODULE - 2);
  for (int v = COMM - 2; 0 <= v; v --) {
    mod_one_array[v] = (long long)mod_one_array[v + 1] * (v + 1) % MODULE;
  }
  int i = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) printf("With Case %d.\n", i);
    scanf("%d %d", &N, &M);
    long long res = count_way(N, M);
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    if (COMPILE) printf_array(ini_array, 0, "ini_array", "int");
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}
