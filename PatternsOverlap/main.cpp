#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;

#define MAX_LEN 3000

char a[MAX_LEN];
char b[MAX_LEN];
bool gram[MAX_LEN][MAX_LEN];
queue < pair<int, int> > qn;

void enqueue(int i, int j) {
  if (!gram[i][j]) {
    qn.push({i, j});
    gram[i][j] = true;
  }
}

bool overlap() {
  int len_a = strlen(a);
  int len_b = strlen(b);
  for (int i = 0; i < len_a; i++) {
    for (int j = 0; j < len_b; j++) {
      gram[i][j] = false;
    }
  }
  while (!qn.empty()) qn.pop();
  enqueue(0, 0);
  while (!qn.empty()) {
    int ll = qn.front().first + 1, rr = qn.front().second + 1;
    if (ll < len_a) {
      if (a[ll] == '*') {
        enqueue(ll, rr - 1);
        for (int k = rr, cnt = 0; k < len_b; k++) {
          if (b[k] == '*') {
            enqueue(ll, k);
          } else {
            if (cnt < 4) { enqueue(ll, k); cnt++; }
            else break;
          }
        }
      } else {
        for (int k = rr; k < len_b; k++) {
          if (b[k] == '*') {
            enqueue(ll, k);
          } else {
            if (a[ll] == b[k]) {
              enqueue(ll, k);
            }
            break;
          }
        }
      }
    }
    if (rr < len_a) {
      if (a[rr] == '*') {
        enqueue(ll - 1, rr);
        for (int k = ll, cnt = 0; k < len_a; k++) {
          if (b[k] == '*') {
            enqueue(k, rr);
          } else {
            if (cnt < 4) { enqueue(k, rr); cnt++; }
            else break;
          }
        }
      } else {
        for (int k = ll; k < len_a; k++) {
          if (b[k] == '*') {
            enqueue(k, rr);
          } else {
            if (a[k] == b[rr]) {
              enqueue(k, rr);
            }
            break;
          }
        }
      }
    }
    qn.pop();
  }
  return gram[len_a - 1][len_b - 1];
}

int main() {
  freopen("large.in", "r", stdin);
  freopen("large.out", "w", stdout);
  int T;
  scanf("%d", &T);
  int i = 0;
  while (i++ < T) {
    a[0] = '0';
    b[0] = '0';
    scanf("%s", a + 1);
    scanf("%s", b + 1);   
    printf("Case #%d: %s\n", i, (overlap() ? "TRUE" : "FALSE"));
  }
}
