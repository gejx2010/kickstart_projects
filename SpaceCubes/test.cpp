#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

using ll = long long;
using ld = long double;
using prl = pair<ll, ll>;

#define LARGE 2005

int T;
int N;
ll X[LARGE], Y[LARGE], Z[LARGE], R[LARGE];
prl Q[LARGE], S[LARGE];

ll fmin(ll* a, ll* r) {
  ll d = INT_MAX, u = INT_MIN;
  for (int i = 1; i <= N; ++i) {
    d = min(d, a[i] - r[i]);
    u = max(u, a[i] + r[i]);
  }
  ll lm = 0;
  for (int i = 1; i <= N; ++i) 
    lm = max(lm, min(a[i] + r[i] - d, u - a[i] + r[i]));
  return lm;
}

ll solve() {
  ll xm = fmin(X, R);
  ll ym = fmin(Y, R);
  ll zm = fmin(Z, R);
  return max(xm, max(ym, zm));
}

int main() {
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i) {
    scanf("%d", &N);
    for (int j = 1; j <= N; ++j) 
      scanf("%lld %lld %lld %lld", &X[j], &Y[j], &Z[j], &R[j]);
    ll r = solve();
    printf("Case #%d: %lld\n", i, r);
  }
  return 0;
}
