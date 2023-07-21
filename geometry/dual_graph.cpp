#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
ll n, m, k, ans;
const ll mod=1e9+7;

pii p[202020], o;
ll h[202020], reg[202020];
vector<vector<pii>> graph(202020);

ll par[404040], out;
ll f(ll x){return x==par[x]?x:par[x]=f(par[x]);}
void uni(ll x, ll y){par[f(x)]=f(y);}

ll ccw(pii a, pii b, pii c)
{
	ll ax=c.x-b.x, ay=c.y-b.y, bx=c.x-a.x, by=c.y-a.y, d=ax*by-ay*bx;
	return (d>0)-(d<0);
}
bool cmp(pii a, pii b)
{
	a=p[a.second], b=p[b.second];
	if((a>o)^(b>o)) return a>b;
	return ccw(a, o, b)>0;
}

ll dis[202][202];

double nx;
struct line{
	double a, b;
	ll i;
	line(pii p, pii q, ll idx){
		if(p>q) swap(p, q);
		a=((double)(q.y-p.y))/(q.x-p.x);
		b=p.y-a*p.x;
		i=idx;
	}
	bool operator<(const line l) const{
		if(a*nx+b!=l.a*nx+l.b) return a*nx+b<l.a*nx+l.b;
		return i<l.i;
	}
};
set<line> st;
bool vt[202020];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	ll i, j, temp=0;
	for(i=0;i<404040;i++) 
		par[i]=i;
	cin>>n>>m;
	for(i=1;i<=n;i++)
		cin>>p[i].x>>p[i].y;
	for(i=0;i<m;i++)
	{
		cin>>k>>j>>h[i];
		graph[k].emplace_back(i, j);
		graph[j].emplace_back(i, k);
	}

	for(i=1;i<=n;i++)
	{
		o=p[i];
		sort(graph[i].begin(), graph[i].end(), cmp);//각도 정렬
		ll u, v;
		//간선의 어느쪽인지 판별
		for(j=1;j<graph[i].size();j++)
		{
			u=2*graph[i][j-1].first+1, v=2*graph[i][j].first;
			if(p[graph[i][j-1].second].x>o.x) u^=1;
			if(p[graph[i][j-1].second].x==o.x&&p[graph[i][j-1].second].y<o.y) u^=1;
			if(p[graph[i][j].second].x>o.x) v^=1;
			if(p[graph[i][j].second].x==o.x&&p[graph[i][j].second].y<o.y) v^=1;
			uni(u, v);
		}
		u=2*graph[i][j-1].first+1, v=2*graph[i][0].first;
		if(p[graph[i][j-1].second].x>o.x) u^=1;
		if(p[graph[i][j-1].second].x==o.x&&p[graph[i][j-1].second].y<o.y) u^=1;
		if(p[graph[i][0].second].x>o.x) v^=1;
		if(p[graph[i][0].second].x==o.x&&p[graph[i][0].second].y<o.y) v^=1;
		uni(u, v);
	}
	i=min_element(p+1, p+n+1)-p;
	out=f(2*graph[i][0].first+1);//외부

	vector<pair<pii, ll>> q;
	for(i=1;i<=n;i++)
		q.emplace_back(p[i], i);

	vector<ll> v;
	for(i=0;i<m;i++)
	{
		v.push_back(f(2*i));
		v.push_back(f(2*i+1));
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	n=v.size();
	//플로이드
	for(i=0;i<n;i++) for(j=0;j<n;j++) if(i!=j) dis[i][j]=1e18;

	for(i=0;i<m;i++)
	{
		ll a=lower_bound(v.begin(), v.end(), f(2*i))-v.begin();
		ll b=lower_bound(v.begin(), v.end(), f(2*i+1))-v.begin();
		dis[a][b]=min(dis[a][b], h[i]);
		dis[b][a]=min(dis[b][a], h[i]);
	}
	for(k=0;k<n;k++) for(i=0;i<n;i++) for(j=0;j<n;j++) dis[i][j]=min(dis[i][j], dis[i][k]+dis[k][j]);
	cin>>m;
	for(i=1;i<=m;i++)
	{
		cin>>j>>k;
		q.emplace_back(pii(j, k), -i);
	}
	sort(q.begin(), q.end());
	for(auto t:q)
	{
		nx=t.x.x;
		if(t.second>0)
		{
			i=t.second;
			nx-=0.5;//삭제 먼저
			for(auto j:graph[i])
			{
				if(p[i].x==p[j.second].x) continue;
				if(!vt[j.first]) continue;
				line l(p[i], p[j.second], j.first);
				st.erase(st.lower_bound(l));			
			}
			nx+=1;//이후 삽입
			for(auto j:graph[i])
			{
				if(p[i].x==p[j.second].x) continue;
				if(vt[j.first]) continue;
				line l(p[i], p[j.second], j.first);
				vt[j.first]=1;
				st.insert(l);			
			}
		}
		else
		{
			i=-t.second;
			auto it=st.lower_bound(line(t.first, pii(mod, 0), 0));
			if(it==st.end()) reg[i]=out;
			else reg[i]=f(2*(it->i)+1);
			reg[i]=lower_bound(v.begin(), v.end(), reg[i])-v.begin();
		}
	}
	reg[0]=lower_bound(v.begin(), v.end(), out)-v.begin();
	for(i=1;i<=m;i++)
		cout<<dis[reg[i-1]][reg[i]]<<'\n';
}