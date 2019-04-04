#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <queue>
#include <stack>
#include <ctime>

using namespace std;

#define LARGE 2005

typedef pair<int, int> pri;

int T;
char A[LARGE], B[LARGE];
bool S[LARGE][LARGE];

stack<pri> Q;

bool solve() {
  while (!Q.empty()) Q.pop();
  memset(S, 0, sizeof S);
  A[0] = '$', B[0] = '$';
  Q.push({0, 0});
  
  int asz = strlen(A), bsz = strlen(B);
  //cout << "asz: " << asz << endl;
  //cout << "bsz: " << bsz << endl;
  //cout << "A: " << A << endl;
  //cout << "B: " << B << endl;
  while (!Q.empty()) {
    auto v = Q.top();
    Q.pop();
    int ra = v.first + 1, rb = v.second + 1;
    if (!S[ra - 1][rb - 1]) S[ra - 1][rb - 1] = 1;
    else continue;
    //cerr << "ra:" << ra << endl;
    //cerr << "rb:" << rb << endl;
    if (asz == ra && rb < bsz) {
      if (B[rb] == '*') {
        Q.push({ra - 1, rb});
      } 
      continue;
    } else if (bsz == rb && ra < asz) {
      if (A[ra] == '*') {
        Q.push({ra, rb - 1});
      } 
      continue;
    } else if (asz == ra && bsz == rb) return true;

    char a = A[ra], b = B[rb];
    //cerr << "a:" << a << endl;
    //cerr << "b:" << b << endl;
    if (a != '*' && b != '*') {
      if (a != b) continue;
      else {
        Q.push({ra, rb});
      }
    } 
    if (a == '*') {
      Q.push({ra, rb - 1});
      int cnt = 0, j = rb;
      while (j < bsz) {
        if (B[j] != '*') ++cnt;
        if (cnt <= 4) {
          Q.push({ra, j});
        } else break;
        ++j;
      }
    }
    if (b == '*') {
      Q.push({ra - 1, rb});
      int cnt = 0, j = ra;
      while (j < asz) {
        if (A[j] != '*') ++cnt;
        if (cnt <= 4) {
          Q.push({j, rb});
        } else break;
        ++j;
      }
    }
  }
  return S[asz - 1][bsz - 1];
}

int main() {
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i) {
    cerr << "Within case " << i << ". " << endl;
    clock_t st = clock();
    scanf("%s", A + 1);
    scanf("%s", B + 1);
    bool r = solve();
    if (r) printf("Case #%d: TRUE\n", i);
    else printf("Case #%d: FALSE\n", i);
    clock_t ed = clock();
    cerr << "Solve it takes times: " << ((float)ed - st) / CLOCKS_PER_SEC << " seconds" << endl;
  }
  return 0;
}
