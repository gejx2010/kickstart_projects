#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <map>
#include <cassert>

#define PR(x) cerr << #x << ": " << x << endl;

using namespace std;

#define LARGE 400006
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0, N = 0, Q = 0;
long long X[LARGE], Y[LARGE], Z[LARGE], L[LARGE], R[LARGE];
long long mmin, mmax;
long long total;
map<long long, int> pos;
multimap<long long, long long> range;
map<long long, int> cord;
map<pair<long long, long long>, int> range_times;
pair<long long, int> rank_array[LARGE << 1];
int rank_sz;
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
  ++left;
  pos[left] = n;
  pos[right] = n;
}

int cur_search(long long k) {
  int l = mmin, r = mmax;
  if (!pos.empty()) {
    if (pos.count(k) != 0) return pos[k];
    map<long long, int>::iterator lit = pos.lower_bound(k);
    if (lit != pos.begin()) {
      --lit;
      r = lit->second;
    }
    map<long long, int>::iterator rit = pos.upper_bound(k);
    if (rit != pos.end()) l = rit->second;
  }
  long long left, right;
  long long mid = 0;
  if (l == r) return l;
  while (l <= r) {
    //PR(l);
    //PR(r);
    mid = (l + r) >> 1;
    //PR(mid);
    get_nth(mid, left, right);
    //PR(left);
    if (left <= k) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }  
  }
  pos[k] = r + 1;
  return r + 1;
}

int bin_search(long long k) {
  int l = 0, r = rank_sz;
  while (l < r) {
    int m = (l + r) >> 1;
    if (rank_array[m].first < k) {
      l = m + 1;
    } else if (k < rank_array[m].first) {
      r = m;
    } else {
      return rank_array[m].second;
    }
  }
  if (r == 0) return rank_array[0].second;
  long long bef = rank_array[r - 1].second;
  long long cur = rank_array[r].second;
  long long rk = rank_array[r - 1].first;
  int t = range_times[make_pair(bef, cur)];
  if (k - rk <= t * (bef - cur - 1)) return bef - 1 - (k - rk - 1) / t;
  else return cur;
}

void count_cordinate() {
  range_times.clear();
  auto lit = range.end();
  --lit;
  long long bef, cur;
  multimap<long long, int> m;
  cord.clear();
  for (int rank = 0; rank < range.size(); --lit, ++rank) {
    //printf ("@count_cord, first: %lld, second: %lld\n", lit->first, lit->second);
    if (rank == 0) {
      bef = lit->first;
      cur = bef;
    } else {
      cur = lit->first;
    }
    // Add current cord
    cord[cur] = (cord.count(cur) == 0) ? 1 : cord[cur] + 1;
    // the same with last
    if (cur != bef) {
      if (!m.empty()) {
        auto mit = m.end();
        --mit;
        int rank = 0;
        //printf ("mit->first: %lld, second: %d\n", mit->first, mit->second);
        while (rank++ < m.size() && cur < mit->first) {
          long long mf = mit->first;
          range_times[make_pair(bef, mf)] = m.size();
          // count cord
          cord[mf] = (cord.count(mf) == 0) ? m.size() : cord[mf] + m.size();
          //printf("cord[%lld]: %d\n", mf, cord[mf]);
          //printf("range_times(%lld, %lld): %d\n", bef, mf, range_times[make_pair(bef, mit->first)]);
          bef = mf;
          m.erase(mf);
          --mit;
        }
      }
      // get range times here
      range_times[make_pair(bef, cur)] = m.size();
      // count cord
      cord[cur] += m.size();
      //printf ("range_times(%lld, %lld): %d\n", bef, cur, range_times[make_pair(bef, cur)]);
      bef = cur;
      // delete all ended here
      m.erase(cur);
    }
    //printf("cord[%lld]: %d\n", cur, cord[cur]);
    if (lit->second < lit->first)
      m.insert(make_pair(lit->second, 1));
  }
  while (!m.empty()) {
    auto mit = m.end();
    --mit;
    long long mf = mit->first;
    //printf("Out of first while, mit->first: %d\n", mf);
    range_times[make_pair(bef, mf)] = m.size();
    // count cord
    cord[mf] = m.size();
    //printf("cord[%lld]: %d\n", mf, cord[mf]);
    //printf ("range_times(%lld, %lld): %d\n", bef, mf, range_times[make_pair(bef, mf)]);
    bef = mf;
    m.erase(mf);
  }
  long long rank = 0;
  rank_sz = 0;
  auto it = cord.end();
  --it;
  for (; rank_sz < cord.size(); --it) {
    if (rank_sz == 0) {
      bef = it->first;
      cur = bef;
    } else {
      cur = it->first;
      rank += range_times[make_pair(bef, cur)] * (bef - cur - 1);
      bef = cur;
    }
    rank += it->second;
    rank_array[rank_sz++] = make_pair(rank, it->first);
    //printf("rank: %lld, first: %d\n", rank, it->first);
  }
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
  clock_t st = clock();
  while (i++ < T) {
    scanf("%d %d", &N, &Q);
    scanf("%d %d %d %d %d %d", &X[0], &X[1], &A[0], &B[0], &C[0], &M[0]);
    scanf("%d %d %d %d %d %d", &Y[0], &Y[1], &A[1], &B[1], &C[1], &M[1]);
    scanf("%d %d %d %d %d %d", &Z[0], &Z[1], &A[2], &B[2], &C[2], &M[2]);
    total = 0;
    range.clear();
    for (int j = 0; j < N; j++) {
      if (1 < j) {
        X[j] = (A[0] * X[j - 1] + B[0] * X[j - 2] + C[0]) % M[0];
        Y[j] = (A[1] * Y[j - 1] + B[1] * Y[j - 2] + C[1]) % M[1];
      }
      L[j] = min(X[j], Y[j]) + 1;
      R[j] = max(X[j], Y[j]) + 1;
      range.insert(make_pair(R[j], L[j]));
      total += R[j] - L[j] + 1;
      //printf("L[%d]: %lld, R[%d]: %lld\n", j, L[j], j, R[j]);
    }
    count_cordinate();
    for (int j = 0; j < Q; j++) {
      if (1 < j)
        Z[j] = (A[2] * Z[j - 1] + B[2] * Z[j - 2] + C[2]) % M[2];
    }
    for (int j = 0; j < Q; j++) {
      Z[j] = Z[j] + 1;
      //printf("Z[%d]: %lld\n", j, Z[j]);
    }
    //mmin = *min_element(L, L+N);
    //PR(mmin);
    //mmax = *max_element(R, R+N);
    //PR(mmax);
    long long res = 0;
    //PR(total);
    //pos.clear();
    for (int j = 0; j < Q; j++) {
      //printf("Cur z: %lld\n", Z[j]);
      if (total < Z[j]) continue;
      int fn = bin_search(Z[j]);
      PR(fn);
      res += (long long)fn * (j + 1);
      //PR(res);
    }
    if (COMPILE) printf_array(ini_array, 0, "ini_array", "int");
    printf("Case #%d: %lld\n", i, res);
  }
  clock_t rt = clock();
  if (TESTTIME) cerr << "Total time spend: " << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds" << endl; 
  return 0;
}
