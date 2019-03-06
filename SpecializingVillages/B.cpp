#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 100001;

void setIn(string s) { freopen(s.c_str(),"r",stdin); }
void setOut(string s) { freopen(s.c_str(),"w",stdout); }

void io(string s = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (sz(s)) {
        setIn(s+".in");
        setOut(s+".out");
    }
}

int V,E;
vpi adj[51];
set<int> ADJ[51];

void addEdge(int a, int b) {
    ADJ[a].insert(b), ADJ[b].insert(a);
}

void solve() {
    cin >> V >> E;
    FOR(i,1,V+1) {
        adj[i].clear();
        ADJ[i].clear();
    }
    pi special = {-1,-1};
    
    F0R(i,E) {
        int A,B,L; cin >> A >> B >> L;
        adj[A].pb({L,B}), adj[B].pb({L,A});
        if (L == 0) special = {A,B};
    }
    FOR(i,1,V+1) {
        sort(all(adj[i]));
        addEdge(i,adj[i][0].s);
    }
    int numEdge = 0; FOR(i,1,V+1) numEdge += sz(ADJ[i]); 
    numEdge /= 2;
    ll ans = 1;
    F0R(i,V-numEdge) ans *= 2;
    if (special != mp(-1,-1)) {
        // cout << sz(ADJ[special.f]) << " " << sz(ADJ[special.s]) << "\n";
        F0R(i,sz(ADJ[special.f])+sz(ADJ[special.s])-2) ans *= 2;
    }
    cout << ans;
}

int main() {
    io("B");
    int T; cin >> T;
    FOR(i,1,T+1) {
        cout << "Case #" << i << ": ";
        solve();
        cout << '\n';
    }
}
/* 
* (Actually read this pls)
    * Rlly bad errors: int overflow, array bounds
    * Less bad errors: special cases (n=1?), set tle
    * Common sense: do smth instead of nothing
*/