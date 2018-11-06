#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <ctime>

#define PR(x) cout << #x << ": " << x << endl;

using namespace std;

#define LARGE 400005
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0, N = 0, Q = 0;
long long X[LARGE], Y[LARGE], Z[LARGE], L[LARGE], R[LARGE];
long long mmin, mmax;
int A[3], B[3], C[3], M[3];
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

void get_nth(int n, long long &left, long long &right) {
  left = 0, right = 0;
  for (int i = 0; i < N; i++) {
    if (L[i] <= n && n <= R[i]) { left += R[i] - n; right += R[i] - n + 1; }
    else if (n < L[i]) { left += R[i] - L[i] + 1; right += R[i] - L[i] + 1; }
  }
  ++left, ++right;
}

int cur_search(int k) {
  int l = mmin, r = mmax;
  int mid = (l + r) >> 1;
  long long left, right;
  while (l < r) {
    PR(l);
    PR(r);
    mid = (l + r) >> 1;
    PR(mid);
    get_nth(mid, left, right);
    PR(left);
    if (left <= k) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  get_nth(r, left, right);
  if (left < k) return 0;
  return r + 1;
}

int main(int argc, char** argv) {
  char* def_ifn = "small.in";
  char* def_ofn = "small.out";
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
    scanf("%d %d", &N, &Q);
    scanf("%d %d %d %d %d %d", &X[0], &X[1], &A[0], &B[0], &C[0], &M[0]);
    scanf("%d %d %d %d %d %d", &Y[0], &Y[1], &A[1], &B[1], &C[1], &M[1]);
    scanf("%d %d %d %d %d %d", &Z[0], &Z[1], &A[2], &B[2], &C[2], &M[2]);
    for (int j = 0; j < N; j++) {
      if (1 < j) {
        X[j] = (A[0] * X[j - 1] + B[0] * X[j - 2] + C[0]) % M[0];
        Y[j] = (A[1] * Y[j - 1] + B[1] * Y[j - 2] + C[1]) % M[1];
      }
      L[j] = min(X[j], Y[j]) + 1;
      R[j] = max(X[j], Y[j]) + 1;
      printf("L[%d]: %lld, R[%d]: %lld\n", j, L[j], j, R[j]);
    }
    for (int j = 0; j < Q; j++) {
      if (1 < j)
        Z[j] = (A[2] * Z[j - 1] + B[2] * Z[j - 2] + C[2]) % M[2] + 1;
      else
        Z[j] = Z[j] + 1;
      printf("Z[%d]: %lld\n", j, Z[j]);
    }
    mmin = *min_element(L, L+N);
    PR(mmin);
    mmax = *max_element(R, R+N);
    PR(mmax);
    long long res = 0;
    for (int j = 0; j < Q; j++) {
      int k = Z[j] + 1;
      int fn = cur_search(k);
      PR(fn);
      res += cur_search(k) * (j + 1);
    }
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    if (COMPILE) printf_array(ini_array, 0, "ini_array", "int");
    printf("Case #%d: %lld\n", i, res);
  }
  return 0;
}
