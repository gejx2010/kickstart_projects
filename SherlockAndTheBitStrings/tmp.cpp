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

ll N,K,P;
ld num[101][1<<16];
bool done[101][1<<16];
vpi need[101];

ld gen(int a, int b) {
    if (done[a][b] == 1) return num[a][b];
    done[a][b] = 1;
    for (auto x: need[a]) {
        // 15-a+x.f to 15
        // 
        if (__builtin_popcount(b>>(15-a+x.f)) != x.s) {
            return num[a][b] = 0;
        }
    }
    if (a == N) return num[a][b] = 1;
    return num[a][b] = gen(a+1,b/2)+gen(a+1,b/2+(1<<15));
}

void solve() {
    cin >> N >> K >> P;
    // N = 100, K = 0, P = 1;
    memset(done,0,sizeof done);
    F0R(i,101) need[i].clear();
    F0R(i,K) {
        int A,B,C; cin >> A >> B >> C;
        need[B].pb({A,C});
    }
    string cur; 
    int a = 0, b = 0;
    while (sz(cur) < N) {
        if (gen(a+1,b/2) >= P) {
            cur += '0';
            b = b/2;
        } else {
            cur += '1';
            P -= gen(a+1,b/2);
            b = b/2+(1<<15);
        }
        a ++;
    }
    cout << cur;
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
