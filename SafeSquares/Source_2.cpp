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

const int MOD = 1000000007;
double PI = 4*atan(1);

int grid[3001][3001], bad[3001][3001];

int main() {
	int T; cin >> T;
	FOR(t,1,T+1) {
	    ll ans = 0;
	    int r,c,k; cin >> r >> c >> k;
	    F0R(i,r+1) F0R(j,c+1) grid[i][j] = bad[i][j] = 0;
	    F0R(i,k) {
	        int x,y; cin >> x >> y;
	        bad[x][y] = 1;
	    }
	    F0Rd(i,r) F0Rd(j,c) if (bad[i][j] == 0) {
	        grid[i][j] = min(min(grid[i+1][j], grid[i][j+1]),grid[i+1][j+1])+1;
	        ans += grid[i][j];
	    }
	    cout << "Case #" << t << ": " << ans << "\n";
	}
}