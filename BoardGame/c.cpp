#include<bits/stdc++.h>
using namespace std;
struct node
{
	int a,b,c,s;
	bool operator<(const node& y)const
	{
		if(a==y.a)return s>y.s;
		return a<y.a;
	}
}x[1000000],y[1000000],z[1000000];
bool cmp(node x,node y)
{
	return x.b<y.b; 
}
int t,n,m,N,M,ans,X,i,j,Z,a[15],b[15],c[3],d[3],A[3000000];
void dfs(int *a,node *x,int &N,int z,int w=3)
{
	if(z==3*n)
	{
		x[N].a=A[++X]=d[0];
		x[N].b=A[++X]=d[1];
		x[N++].c=A[++X]=d[2];
		return;
	}
	for(int i=0;i<3&&i<=w;i++)if(c[i]<n)
	{
		c[i]++;
		d[i]+=a[z];
		dfs(a,x,N,z+1,min(max(i+1,w),3));
		c[i]--;
		d[i]-=a[z];
	}
}
void work(int l,int r)
{
	if(l==r)return;
	int mid=l+r>>1,i,j,k;
	work(l,mid);
	work(mid+1,r);
	for(i=l,j=mid+1;i<=mid&&j<=r;)if(z[i].b>=z[j].b)
	{
		if(~z[j].s)for(k=z[j].c-1;k;k^=k&-k)z[j].s-=A[k]<<1;
		j++;
	}
	else
	{
		if(!~z[i].s)for(k=z[i].c;k<=X;k+=k&-k)A[k]++;
		i++;
	}
	for(;j<=r;j++)if(~z[j].s)for(k=z[j].c-1;k;k^=k&-k)z[j].s-=A[k]<<1;
	for(i--;i>=l;i--)if(!~z[i].s)for(k=z[i].c;k<=X;k+=k&-k)A[k]--;
	sort(z+l,z+r+1,cmp);
}	
int main()
{
	freopen("large.in","r",stdin);
	freopen("large.out","w",stdout);
	scanf("%d",&t);
	for(int xxx=1;xxx<=t;xxx++)
	{
        clock_t st = clock();
		printf("Case #%d: ",xxx);
		scanf("%d",&n);
		for(i=0;i<3*n;i++)scanf("%d",a+i);
		for(i=0;i<3*n;i++)scanf("%d",b+i);
		N=M=X=Z=0;
		dfs(a,x,N,0,0);
		dfs(b,y,M,0);
		sort(A+1,A+X+1);
		X=unique(A+1,A+X+1)-A-1;
		for(i=0;i<N;i++)
		{
			x[i].a=lower_bound(A+1,A+X+1,x[i].a)-A;
			x[i].b=lower_bound(A+1,A+X+1,x[i].b)-A;
			x[i].c=lower_bound(A+1,A+X+1,x[i].c)-A;
			x[i].s=0;
			z[Z++]=x[i];
		}
		for(i=0;i<M;i++)
		{
			y[i].a=lower_bound(A+1,A+X+1,y[i].a)-A;
			y[i].b=lower_bound(A+1,A+X+1,y[i].b)-A;
			y[i].c=lower_bound(A+1,A+X+1,y[i].c)-A;
			y[i].s=-1;
			z[Z++]=y[i];
		}
		fill(A+1,A+X+1,0);
		sort(z,z+Z);
		for(i=0;i<Z;i++)if(~z[i].s)for(j=z[i].b-1;j;j^=j&-j)z[i].s+=A[j];
		else for(j=z[i].b;j<=X;j+=j&-j)A[j]++;
		fill(A+1,A+X+1,0);
		for(i=0;i<Z;i++)swap(z[i].a,z[i].c);
		sort(z,z+Z);
		for(i=0;i<Z;i++)if(~z[i].s)for(j=z[i].b-1;j;j^=j&-j)z[i].s+=A[j];
		else for(j=z[i].b;j<=X;j+=j&-j)A[j]++;
		fill(A+1,A+X+1,0);
		sort(z,z+Z);
		for(i=0;i<Z;i++)swap(z[i].b,z[i].c);
		for(i=0;i<Z;i++)if(~z[i].s)for(j=z[i].b-1;j;j^=j&-j)z[i].s+=A[j];
		else for(j=z[i].b;j<=X;j+=j&-j)A[j]++;
		fill(A+1,A+X+1,0);
		work(0,Z-1);
		for(i=ans=0;i<Z;i++)ans=max(ans,z[i].s);
		printf("%.9lf\n",(double)ans/M);
        cerr << "times takes: " << ((float)clock() - st) / CLOCKS_PER_SEC << endl;
	}
	return 0;
}

