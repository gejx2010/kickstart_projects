#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define CON_NUM 1000000007
#define DIV_NUM 12

int square_count(int n, int m) {
  long long a = 0, b = 0;
  if (n <= m) { a = n, b = m; }
  else { a = m, b = n; }
  long long med = a * (a - 1); 
  med %= CON_NUM;
  med *= a + 1;
  med %= CON_NUM;
  med *= (2 * b - a);
  med %= CON_NUM;
  for (int i = 0; i < DIV_NUM; i++) {
    if (med % 12 == 0) {
      return med / 12;
    } else {
      med += CON_NUM;
    }
  }
}

int main() {
  freopen("large.in", "r", stdin);
  freopen("large.out", "w", stdout);
  int T = 0;
  scanf("%d", &T);
  int i = 0;
  while (i++ < T) {
    int n = 0, m = 0;
    scanf("%d %d", &n, &m);
    printf("Case #%d: %d\n", i, square_count(n, m));
  }
  return 0;
}
