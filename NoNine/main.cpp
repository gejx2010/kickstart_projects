#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <ctime>

#define PR(x) cerr << #x << ": " << x << endl;
#define ii(x) x - '0'

using namespace std;

#define LARGE 200001
#define COMPILE false
#define TESTTIME false

int ini_array[LARGE], sum_array[LARGE];
char a[100], b[100];

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

void ll_to_a(long long num, char* a) {
  long long l = num, dd = 10, r = 0, rank = 0;
  while (0 < l) {
    r = l % dd;
    a[rank++] = '0' + r;
    l = l / dd;
  }
  a[rank] = '\0';
}

long long div_9(long long L, long long R) {
  if (R < L) return 0;
  long long ll = L % 9, nl = L / 9;
  long long lr = R % 9, nr = R / 9;
  return (nr - nl) + ((ll == 0) ? 1 : 0); 
}

long long find_lower(long long R) {
  return R - (1 + R % 10);
}

long long find_higher(long long L) {
  return L + (9 - L % 10);
}

long long comp_pow(int base, int n) {
  long long sum = 1;
  for (int i = 0; i < n; i++) {
    sum *= base;
  }
  return sum;
}

// solve no nine with [0, n]
long long get_no_nine(long long n) {
  ll_to_a(n, a);
  PR(a);
  long long sum = n + 1;
  int len_a = strlen(a);
  long long bef = ii(a[len_a - 1]);
  PR(sum);
  PR(bef);
  for (int i = len_a - 2; 0 <= i; i--) {
    if (0 < i) {
      sum -= bef * comp_pow(9, i);
      PR(sum);
      sum += bef * comp_pow(9, i - 1);
      PR(sum);
      bef = bef * 10 + ii(a[i]);
    } else {
      sum -= bef;
      sum += div_9(0, bef - 1);
    }
    PR(sum);
    PR(bef);
  }
  sum -= div_9(0, n);
  return sum;
}

long long solve(long long L, long long R) {
  // get [0, L] & [0, R]
  long long nl = get_no_nine(L);
  long long nr = get_no_nine(R);
  PR(nl);
  PR(nr);
  return nr - nl + 1;
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
  while (i++ < T) {
    clock_t st = clock();
    long long L = 0, R = 0;
    scanf("%lld %lld", &L, &R);
    if (TESTTIME) printf("With Case %d.\n", i);
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    if (COMPILE) printf_array(ini_array, 0, "ini_array", "int");
    PR(L);
    PR(R);
    long long ans = solve(L, R);
    PR(ans);
    printf("Case #%d: %lld\n", i, ans);
  }
  return 0;
}
