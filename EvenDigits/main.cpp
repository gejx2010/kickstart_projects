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

int ini_array[LARGE], sum_array[LARGE];

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

long long eight_all(int n) {
  long long sum = 0, mul = 1;
  for (int i = 0; i < n; i++, mul *= 10) sum += 8 * mul;
  return sum;
}

long long calc(long long n) {
  // find the higgest odd bit and ites leave
  long long mul = 1, leave = 0;
  int last = 0, i = 0, cur_bit = 0, last_bit = 0;
  while (mul <= n) {
    i++;
    cur_bit = (n / mul) % 10;
    if (cur_bit % 2 != 0) { last_bit = cur_bit; last = i; leave = n % mul; }
    mul *= 10;
  }
  if (last == 0) return 0;
  if (last_bit == 9) return 1 * pow(10, last - 1) + leave - eight_all(last - 1);
  return min(1 * pow(10, last - 1) - leave, 1 * pow(10, last - 1) + leave - eight_all(last - 1));
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
  int i = 0;
  long long n = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) printf("With Case %d.\n", i);
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    if (COMPILE) printf_array(ini_array, 0, "ini_array", "int");
    scanf("%lld", &n);
    printf("Case #%d: %lld\n", i, calc(n));
  }
  return 0;
}
