#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

int main(int argc, char** argv) {
  if (argc <= 1) { printf("Please give file parameters;"); return -1;}
  string ifn = string(strtok(argv[1], "."));
  printf("%s\n", (ifn + ".out").c_str());
  freopen((ifn + ".in").c_str(), "r", stdin);
  freopen((ifn + ".out").c_str(), "w", stdout);
  int T = 0;
  scanf("%d", &T);
  int i = 0;
  while (i++ < T) {
    long long K = 0;
    scanf("%lld\n", &K);
    int res = 0, orig_num = 1, detect_num = 0;
    for (int j = 0; j < 62; j++) {
      detect_num = (orig_num << j);
      if ((K & detect_num) != 0) {
        if ((K & (detect_num << 1)) != 0) res = 1;
        break;
      }
    }
    printf("Case #%d: %d\n", i, res); 
  }
  return 0;
}
