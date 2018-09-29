#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  freopen("large.in", "r", stdin);
  freopen("large.out", "w", stdout);
  int T;
  scanf("%d\n", &T);
  int i = 0;
  while (i < T) {
    int m, n;
    scanf("%d %d\n", &m, &n);
    long long t = (m < n) ? m : n;
    i++;
    printf("Case #%d: %lld\n", i, t * (long long)(t + 1) / 2);
  }
  return 0;
}
