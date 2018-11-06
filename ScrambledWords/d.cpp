#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define ii pair<int,int>
#define INF 1000000100
#define INFLL 1000000000000000100ll
#define UQ(x) (x).resize(distance((x).begin(),unique(all((x)))))
#define mid(x,y) (((x)+(y))>>1)
#define M 1000000007ll
#define BASE 1299827ll
ll expo(ll a,ll b) {
	if (b==0ll) return 1ll;
	ll x=expo(a,b/2ll);
	if (b%2ll) return (((x*x)%M)*a)%M;
	return (x*x)%M;
}

int tc;
int m;
string d[20005];
ll h[20005];
bool has[20005];
int cnt[20005][26];

vector<int> v[100005];
multimap<pair<ll,pair<char,char> >,int> val[100005];
char s[1000005];
int n;
ll A,B,C,D;
ll x[1000005];
int cur[26];

void search(int l,pair<ll,pair<char,char> > p) {
	//printf("search \n");
	auto it=val[l].find(p);
	while (it!=val[l].end() && it->first==p) {
		//for (int j=0;j<26;j++) assert(cnt[it->second][j]==cur[j]);
		has[it->second]=1;
		++it;
	}
	val[l].erase(p);
}
int main() {
    freopen("large.in", "r", stdin);
    freopen("large.out", "w", stdout);
    clock_t start = clock();
	cin>>tc;
	for (int kk=1;kk<=tc;kk++) {
		cin>>m;
		memset(has,0,sizeof(has));
		for (int l=1;l<=100000;l++) {
			v[l].clear();
			val[l].clear();
		}
		memset(cnt,0,sizeof(cnt));
		memset(h,0,sizeof(h));
		for (int i=0;i<m;i++) {
			cin>>d[i];
			v[sz(d[i])].pb(i);
			for (int j=1;j<sz(d[i])-1;j++) {
				cnt[i][d[i][j]-'a']++;
			}
			for (int j=0;j<26;j++) {
				h[i]=(h[i]*BASE+(ll)cnt[i][j])%M;
			}
			val[sz(d[i])].insert(mp(mp(h[i],mp(d[i][0],d[i].back())),i));
			//printf("%d: %c %c %lld\n", i,d[i][0],d[i].back(),h[i]);
		}
		cin>>s[0];
		cin>>s[1];
		cin>>n;
		cin>>A;
		cin>>B;
		cin>>C;
		cin>>D;
		//printf("%lld %lld %lld %lld\n", A,B,C,D);
		x[0]=(ll)s[0];
		x[1]=(ll)s[1];
		for (int i=2;i<n;i++) {
			x[i] = (A*(ll)(x[i-1])+B*(ll)(x[i-2])+C)%D;
			s[i]=(char)(97+(int)(x[i]%26ll));
		}
		s[n]=0;
		//printf("%s\n", s);
		for (int l=1;l<=100000;l++) {
			if (v[l].empty()) continue;
			memset(cur,0,sizeof(cur));
			if (l>n) break;
			//printf("l = %d:\n", l);
			ll curh=0ll;
			for (int i=1;i<l-1;i++) {
				cur[s[i]-'a']++;
			}
			for (int j=0;j<26;j++) {
				curh=(curh*BASE+(ll)cur[j])%M;
			}
			search(l,mp(curh,mp(s[0],s[l-1])));
			//printf("i = %d, %c %c curh = %lld\n", 0,s[0],s[l-1],curh);
			for (int i=l;i<n;i++) {
				cur[s[i-l+1]-'a']--;
				curh=(curh-expo(BASE,25-(s[i-l+1]-'a'))+M)%M;
				cur[s[i-1]-'a']++;
				curh=(curh+expo(BASE,25-(s[i-1]-'a')))%M;
				search(l,mp(curh,mp(s[i-l+1],s[i])));
				//printf("i = %d, %c %c curh = %lld\n", i-l+1,s[i-l+1],s[i],curh);
			}
		}
		int ans=0;
		for (int i=0;i<m;i++) {
			if (has[i]) ans++;
		}
		printf("Case #%d: %d\n", kk,ans);
		fprintf(stderr, "%d\n", kk);
	}
    cout << "Total time" << ((float) clock() - start) / CLOCKS_PER_SEC << endl;
}
