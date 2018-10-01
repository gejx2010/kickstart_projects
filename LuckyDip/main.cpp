#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <ctime>

using namespace std;

#define LARGE 200001
#define COMPILE false
#define TESTTIME false

int ini_array[LARGE];
long long sum_array[LARGE];

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

double calc(int N, int K) {
  // calc sum and sum-sum
  int turn = 0, i = 0;
  long long sum = 0, ss = 0;
  sum_array[0] = 0;
  for (i = 0; i < N; i++) {
    sum_array[i + 1] = sum_array[i] + ini_array[i];
    if (COMPILE) printf("@calc:, sum_array[%d]: %lld\n", i + 1, sum_array[i + 1]);
  }
  sum = sum_array[N];
  double res = (double) sum / N;
  while (turn++ < K) {
    int gr = upper_bound(ini_array, ini_array + N, res) - ini_array;
    if (COMPILE) printf("In while, before, res: %f, gr: %d.\n", res, gr);
    res = (double)(sum_array[N] - sum_array[gr]) / N + (double)gr / N * res;
    if (COMPILE) printf("In while, after, res: %f.\n", res, gr);
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
  int T = 0;
  scanf("%d", &T);
  if (COMPILE) printf("Get T: %d\n", T);
  int i = 0, N = 0, K = 0;
  while (i++ < T) {
    clock_t st = clock();
    scanf("%d %d", &N, &K);
    int j = 0;
    while (j < N) 
      scanf("%d", &ini_array[j++]);
    if (TESTTIME) printf("With Case %d.\n", i);
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    if (COMPILE) printf_array(ini_array, 0, "ini_array", "int");
    sort(ini_array, ini_array + N);
    printf("Case #%d: %.6f\n", i, calc(N, K));
  }
  return 0;
}
