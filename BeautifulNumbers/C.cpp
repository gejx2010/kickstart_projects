#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <complex>
#include <ctime>
#include <cassert>
#include <functional>

using namespace std;

typedef long long ll;
typedef vector<int> VI;
typedef pair<int,int> PII;

#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))

const ll INF = (ll)1E18;

map<ll, PII> mem; // PII: (len, base)
ll root(ll x) {
  double r = sqrt((double)x);
  ll sol = (ll)r;
  if (sol * sol == x) return sol;
  if ((sol+1)*(sol+1) == x) return sol+1;
  if ((sol-1)*(sol-1) == x) return sol-1;
  return -1;
}
int main() {
  freopen("input", "r", stdin);
  freopen("output", "w", stdout);
  for (ll base = 2; base <= 1000000; base++) {
    ll val = 0;
    REP(len,0,63) {
      if (val > INF/base) break;
      val = val * base + 1;
      if (len >= 3) {
        auto it = mem.find(val);
        if (it == mem.end() || it->second.first < len) {
          mem[val] = PII(len, base);
        }
      }
    }
  }
  int cs;
  cin >> cs;
  REP(csn, 1, cs + 1) {
    printf("Case #%d: ", csn);
    ll n;
    cin >> n;
    if (mem.find(n) != mem.end()) {
      cout << mem[n].second << endl;
    } else {
      ll D = 1-4ll*(1-n);
      if (D >= 0 && root(D) != -1) {
        ll r = root(D);
        if ((r-1) % 2 == 0 && (r-1)/2 != 1) {
          cout << (r-1)/2 << endl;
          continue;
        }
      }
      cout << n - 1 << endl;
    }
  }
  return 0;
}
