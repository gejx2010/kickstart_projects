/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define int ll

ll INF = 1000000000000000000;
double PI = 4*atan(1);

ll getpo(ll b, int x) {
    ll b1 = 1;
    F0R(i,x) b1 *= b;
    return b1;
}

ll ret(ll mid, int i) {
    ll ans = 0;
    F0R(it,i) ans += getpo(mid,it);
    return ans;
}

ll get(ll N, int i) {
    ll lo = 2, hi = pow(N,(double)1/(i-1));
    if (lo>hi) return INF;
    while (lo<hi) {
        int mid = (lo+hi)/2;
        if (ret(mid,i) < N) lo = mid+1;
        else hi = mid;
    }
    if (ret(lo,i) == N) return lo;
    return INF;
}

ll solve(ll N) {
    ll ans = N-1;
    FOR(i,2,61) ans = min(ans,get(N,i));
    return ans;
}

main() {
	int T; cin >> T;
	FOR(t,1,T+1) {
	    ll N; cin >> N;
	    cout << "Case #" << t << ": " << solve(N) << "\n";
	}
}