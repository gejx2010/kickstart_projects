#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<double,double> pd;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;

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

template<class T, int SZ> struct BIT {
    T bit[SZ+1];
    
    BIT() { memset(bit,0,sizeof bit); }
    
    void upd(int k, T val) { // add val to index k
        for( ;k <= SZ; k += (k&-k)) bit[k] += val;
    }
    
    T query(int k) {
        T temp = 0;
        for (;k > 0;k -= (k&-k)) temp += bit[k];
        return temp;
    }
    T query(int l, int r) { return query(r)-query(l-1); } // range query [l,r]
};

BIT<int,1000000> ra;

ll N, A, B, C, D, E, F, M;
pl q[2][500000];
vpi P;

void fill1() {
    ra = BIT<int,1000000>();
    for (int i = 0; i < sz(P); ) {
        int I = i;
        while (i < sz(P) && P[i].f == P[I].f) i++;
        FOR(j,I,i) {
            q[0][j].f = ra.query(1,P[j].s-1);
            q[0][j].s = ra.query(P[j].s+1,1000000);
        }
        FOR(j,I,i) {
            ra.upd(P[j].s,1);
            // cout << "HI " << j << "\n";
        }
    }
}

void fill2() {
    ra = BIT<int,1000000>();
    for (int i = sz(P)-1; i >= 0; ) {
        int I = i;
        while (i >= 0 && P[i].f == P[I].f) i--;
        FOR(j,i+1,I+1) {
            q[1][j].f = ra.query(1,P[j].s-1);
            q[1][j].s = ra.query(P[j].s+1,1000000);
        }
        FOR(j,i+1,I+1) ra.upd(P[j].s,1);
    }
}

void solve() {
    // N = 500000; 
    cin >> N;
    P.resize(N);
    cin >> P[0].f >> P[0].s >> A >> B >> C >> D >> E >> F >> M;
    // M = 1000000;
    // P[0].f = P[0].s = A = B = C = D = rand() % 1000000;
    FOR(i,1,sz(P)) {
        P[i].f = (A*P[i-1].f+B*P[i-1].s+C)%M;
        P[i].s = (D*P[i-1].f+E*P[i-1].s+F)%M;
    }
    F0R(i,sz(P)) {
        assert(P[i].f < M);
        P[i].f ++, P[i].s ++;
    }
    sort(all(P));
    fill1();
    fill2();
    ll ans = N*(N-1)*(N-2)/6;
    F0R(i,sz(P)) {
        ans -= q[0][i].f*q[1][i].s+q[0][i].s*q[1][i].f;
    }
    cout << ans;
}

int main() {
    freopen("large.in","r",stdin);
    freopen("large.out","w",stdout);
    int T; cin >> T;
    FOR(i,1,T+1) {
        cout << "Case #" << i << ": ";
        solve();
        cout << endl;
    }
}

// read the question correctly (is y a vowel? what are the exact constraints?)
// look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
