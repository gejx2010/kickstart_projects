/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<ll,ll> pii;
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

int mx[500000];
ll N, L1, R1, A, B, C1, C2, M;
int lst, tot = 0, mxrem = 0;
vector<pii> xy, z; 
vector<pair<pii,int>> xco;
set<int> cur;

void init() {
    cin >> N >> L1 >> R1 >> A >> B >> C1 >> C2 >> M;
    tot = 0, mxrem = 0;
	F0R(i,N) mx[i] = 0;
	xy.clear(), z.clear(); xco.clear();
	
	xy.pb({L1,R1});
	F0R(i,N-1) 
	    xy.pb({(A*xy[i].f+B*xy[i].s+C1) % M, (A*xy[i].s+B*xy[i].f+C2) % M});
	F0R(i,N) z.pb({min(xy[i].f,xy[i].s),max(xy[i].f,xy[i].s)});
	F0R(i,N) {
	    xco.pb({{z[i].f,1},i});
	    xco.pb({{z[i].s+1,-1},i});
	}
	sort(xco.begin(),xco.end());
}

int main() {
	int T; cin >> T;
	FOR(t,1,T+1) {
	    init();
	    int it = 0;
	    while (it < (int)xco.size()) {
	        int x = xco[it].f.f;
	        if (cur.size()) tot += x-lst;
	        if (cur.size() == 1) {
	            mx[*cur.begin()] += x-lst;
	            mxrem = max(mxrem,mx[*cur.begin()]);
	        }
	        while (xco[it].f.f == x) {
	            if (xco[it].f.s == -1) cur.erase(xco[it].s);
	            else cur.insert(xco[it].s);
	            it++;
	        }
	        lst = x;
	    }
	    cout << "Case #" << t << ": " << tot-mxrem << "\n";
	}
}