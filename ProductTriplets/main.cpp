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

#define LARGE 10001
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0, N = 0;
vector<int> A;
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

bool suffix(int a, int b, int c) {
  return ((long long)a == (long long)b * c or (long long)b == (long long)a * c or (long long)c == (long long)a * b);
}

int find_rank(int* a, int left, long long cur) {
  int start = left, end = N, mid = (start + end) >> 1;
  while (start < end) {
    mid = (start + end) >> 1;
    if (a[mid] == cur) return mid;
    else if (a[mid] < cur) { start = mid + 1; }
    else { end = mid; }
  }
  return mid;
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
    scanf("%d", &N);
    int c = 0;
    A.clear();
    for (int i = 0; i < N; i++)  {
      scanf("%d", &c);
      A.push_back(c);
    }
    sort (A.begin(), A.end());
    long long res = 0;
    int rank = 0;
    for (int i = 0; i < N; i++) {
      rank = 0;
      for (int j = i + 1; j < N; j++) {
        if (A[i] == 0) {
          if (A[j] == 0) {
            res += N - j - 1;
           
          }       
          continue;
        }
        long long cur = A[i] * A[j];
        //PR(i);
        //PR(j);
        //PR(cur);
        vector<int>::iterator left = lower_bound(A.begin() + j + 1, A.end(), cur);
        if (left == A.end()) break;
        int l = left - A.begin();
        //PR(l);
        vector<int>::iterator right = upper_bound(A.begin() + j + 1, A.end(), cur);
        int r = right - A.begin();
        //PR(r);
        if (l < N && suffix(A[i], A[j], A[l])) res += r - l;
        //PR(res);
      }
    }
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    if (COMPILE) printf_array(ini_array, 0, "ini_array", "int");
    printf("Case #%d: %lld\n", i, res);
  }
  return 0;
}
