#include <iostream>
#include <fstream>
#include <cstdio>
#include <climits>
#include <cmath>
#include <cstdlib>

using namespace std;

int x[3000], y[3000], z[3000], r[3000];

int max(int x, int y) {
  return x < y ? y : x;
}

int max(int x, int y, int z) {
  if (x < y) {
    return max(y, z);
  } else {
    return max(x, z);
  }
}

int find_min(int* e, int* r, int N) {
  int ans = INT_MAX;
  for (int i = 0; i < N; i++) {
    if (e[i] - r[i] < ans) ans = e[i] - r[i];
  }
  return ans;
}

int find_max(int* e, int* r, int N) {
  int ans = INT_MIN;
  for (int i = 0; i < N; i++) {
    if (ans < e[i] + r[i]) ans = e[i] + r[i];
  }
  return ans;
}

int solve(int* e, int* r, int N) {
  // find min cross-edge distance
  int left_min = find_min(e, r, N);
  int right_max = find_max(e, r, N);
  double medium = (double)(left_min + right_max) / 2.0;
  int max_rad = 0;
  //printf("left_min: %d, right_max: %d, medium: %f\n", left_min, right_max, medium);
  for (int i = 0; i < N; i++) {
    //printf("cur point: (%d, %d)\n", e[i], r[i]);
    //printf("before, max_rad: %d\n", max_rad);
    if (e[i] <= medium) {
      if (max_rad < e[i] + r[i] - left_min)
        max_rad = e[i] + r[i] - left_min;
    } else {
      if (max_rad < right_max - (e[i] - r[i])) 
        max_rad = right_max  - (e[i] - r[i]);
    }
    //printf("after, max_rad: %d\n", max_rad);
  }
  return max_rad;
}

int find_max_one_axis(int e, int r, int left, int right) {
  double len = llabs(left - right);
  double half_len = (double)len / 2.0;
  if (llabs(left - e) < half_len) {
    return max(llabs(left - (e + r)), llabs(left - (e - r)));
  } else {
    return max(llabs(right - (e + r)), llabs(right - (e - r)));
  }
}

int find_max_one(int* x, int* y, int* z, int* r, int N, int left_x, int left_y, int left_z, int right_x, int right_y, int right_z) {
  int max_rad = 0;
  for (int i = 0; i < N; i++) {
    int cur_rad_1 = find_max_one_axis(x[i], r[i], left_x, right_x);
    int cur_rad_2 = find_max_one_axis(y[i], r[i], left_y, right_y);
    int cur_rad_3 = find_max_one_axis(z[i], r[i], left_z, right_z);
    int cur_rad = max(cur_rad_1, cur_rad_2, cur_rad_3);
    max_rad = max_rad < cur_rad ? cur_rad : max_rad;
  }
  return max_rad;
}

int solve(int* x, int* y, int* z, int* r, int N) {
  int min_x = find_min(x, r, N);
  int min_y = find_min(y, r, N);
  int min_z = find_min(z, r, N);
  int max_x = find_max(x, r, N);
  int max_y = find_max(y, r, N);
  int max_z = find_max(z, r, N);
  int max_rad = INT_MAX;
  int max_rad_1 = find_max_one(x, y, z, r, N, min_x, min_y, min_z, max_x, max_y, max_z);
  max_rad = max_rad < max_rad_1 ? max_rad : max_rad_1;
  //printf("max_rad_1: %d\n", max_rad_1);
  int max_rad_2 = find_max_one(x, y, z, r, N, min_x, min_y, max_z, max_x, max_y, min_z);
  max_rad = max_rad < max_rad_2 ? max_rad : max_rad_2;
  //printf("max_rad_2: %d\n", max_rad_2);
  int max_rad_3 = find_max_one(x, y, z, r, N, min_x, max_y, min_z, max_x, min_y, max_z);
  max_rad = max_rad < max_rad_3 ? max_rad : max_rad_3;
  //printf("max_rad_3: %d\n", max_rad_3);
  int max_rad_4 = find_max_one(x, y, z, r, N, max_x, min_y, min_z, min_x, max_y, max_z);
  max_rad = max_rad < max_rad_4 ? max_rad : max_rad_4;
  //printf("max_rad_4: %d\n", max_rad_4);
  return max_rad;
}

int main() {
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
  int T = 0;
  scanf("%d\n", &T);
  int i = 0;
  while (i++ < T) {
    int N = 0;
    scanf("%d\n", &N);
    int j = 0;
    while (j < N) {
      scanf("%d %d %d %d", &x[j], &y[j], &z[j], &r[j]);
      j++;
    }
    int ans = solve(x, y, z, r, N);
    printf("Case #%d: %d\n", i, ans);
  }
  return 0;
}

