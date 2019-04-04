#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

#define LARGE 1000000007

int T;
ll R, C;
ll SP;

ll cmp_step(ll a, ll k) {
  ll r = 1;
  while (k) {
    if (k & 1) r = (r * a) % LARGE;
    a = (a * a) % LARGE;
    k >>= 1;
  }
  return r;
}

void precmp() {
  SP = cmp_step(12, LARGE - 2);
}

ll cmp(ll R, ll C) {
  if (C < R) return cmp(C, R);
  --R, --C;
  ll r = ((C - R) * 2) % LARGE;
  r = (r + (R + 1)) % LARGE;
  r = (r * R) % LARGE;
  r = (r * (R + 1)) % LARGE;
  r = (r * (R + 2)) % LARGE;
  r = (r * SP) % LARGE;
  return r;
}

ll solve() {
  return cmp(R, C);
}

int main() {
  precmp();
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i) {
    scanf("%lld %lld", &R, &C);
    ll r = solve();
    printf("Case #%d: %lld\n", i, r);
  }
  return 0;
}
