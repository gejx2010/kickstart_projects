#include <iostream>
#include <cstdio>
#include <cstring>

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
  i++;
  printf("Case #%d: %.9f\n", i, (m - n) / (float)(m + n));
  }
  return 0;
}
