/*
 by skydog
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <deque>
#include <cassert>
#include <list>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> l4;

#define mp make_pair
#define pb push_back
#define db(x) cerr << #x << " = " << x << endl

typedef unsigned long long ull;


const int maxn = 2e5+1;
ll a[maxn];
int n, q;
ll ngth(ll v)
{
  ll cnt = 0;
  for (int i = 1; i <= n; ++i)
    cnt += upper_bound(a+i, a+n+1, a[i-1]+v)-(a+i);
  //cerr << "ngth " << v << " =  " << cnt << endl;
  return cnt;
}
ll count(ll v)
{
  return ngth(v)-ngth(v-1);
}
ll get(ll k)
{
  ll l = 0, r = a[n], mid, ans = -1;
  while (l <= r)
    {
      mid = (l+r)>>1;
      if (ngth(mid) >= k)
        {
	  ans = mid;
	  r = mid-1;
        }
      else
        {
	  l = mid+1;
        }
    }
  assert(ans != -1);
  return ans;
    
}
ll s[maxn];
void solve()
{
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", a+i);
  a[0] = 0;
  for (int i = 1; i <= n; ++i)
    a[i] += a[i-1];
  s[0] = 0;
  for (int i = 1; i <= n; ++i)
    s[i] = s[i-1] + a[i];
  /*
    vector<ll> all;
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            all.pb(a[j]-a[i-1]);
    sort(all.begin(), all.end());
    cerr << "all\n";
    for (auto e : all)
    cerr << e << " ";
    cerr << endl;
  */
  for (int t = 0; t < q; ++t)
    {
      ll l, r, ans = 0;
      scanf("%lld %lld", &l, &r);
      ll lv = get(l), rv = get(r);
      if (lv == rv)
	ans = (r-l+1)*lv;
      else
        {
	  ans += lv * (ngth(lv)-l+1) + rv * (r-ngth(rv-1));
	  for (int i = 1; i <= n; ++i)
            {
	      ll far = lower_bound(a+i, a+n+1, a[i-1]+rv)-a-1;
	      ll close = upper_bound(a+i, a+n+1, a[i-1]+lv)-a;
	      ans += s[far]-s[close-1] - a[i-1]*(far-close+1);
            }
        }
      printf("%lld\n", ans);
    }
    
}
int main()
{
  freopen("large.in", "r", stdin);
  int T;
  scanf("%d", &T);
  for (int kase = 1; kase <= T; ++kase)
    {
      cerr << "solve " << kase << endl;
      printf("Case #%d:\n", kase);
      solve();
    }
}
