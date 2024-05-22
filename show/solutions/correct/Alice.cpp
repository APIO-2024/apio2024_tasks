#include"Alice.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
namespace A{
const ll mod=4096;
ll n,i,j,k,l,r,x,y,z,w,s,t,a[1100000],b[1100000],adj[5500][5500],c[1100000],d[1100000],h[1100000],e,m,perm[1100000];
vector<ll> v[1100000];
vector<pair<ll,ll>> u;
vector<pair<int,int>> p;
void link(ll x,ll y,ll z)
{
    ll i;
    for(i=y;i<=z;i++)
    {
        perm[i]=x;
        if(adj[x][i]==0)
        {
            adj[x][i]=1;
            adj[i][x]=1;
        }
    }
}
pair<ll,ll> f(ll x,ll y)
{
    //printf("%lld(%lld)\n",ll(x),y);
    c[x]=1;
    ll i,mn=100000,mx=0;
    pair<ll,ll> p;
    for(i=0;i<h[x];i++)
    {
        if(v[x][i]==y)
            continue;
        p=f(v[x][i],x);
        mn=min(mn,p.first);
        mx=max(mx,p.second);
    }
    if(h[x]<=1)
    {
        mn=min(mn,x);
        mx=max(mx,x);
    }
    return {mn,mx};
}
void Clear()
{
    ll i;
    for(i=1;i<=4991;i++)
    {
        v[i].clear();
        h[i]=0;
        b[i]=0;
        a[i]=0;
        c[i]=0;
        d[i]=0;
        perm[i]=0;
    }
    for(i=1;i<=4991;i++)
        for(j=1;j<=4991;j++)
    {
        adj[i][j]=0;
    }
}
vector<pair<int,int>> Alice()
{
    for(i=1;i<=4991;i++)
        adj[i][i]=1;
    k=setN(4991);
    i=1;
        while(k>0)
        {
           a[i]=k%mod;
           k/=mod;
           i++;
        }
        for(i=1;i<=31;i++)
        {
            x=i;
            j=1;
            while(x>0)
            {
                if(x&1)
                {
                    b[i]^=a[j];
                }
                x>>=1;
                j++;
            }
            b[i]++;
        }
        for(i=1;i<=31;i++)
        {
            if(i!=31)
            link(b[i],(i-1)*161+1,i*161);
            else
            {
                link(b[i],(i-1)*161+1,4991);
            }
        }
        n=4991;
        for(i=1;i<=n;i++)
        {
            if(c[i]==2)
                continue;
            x=i;
            y=0;
            while(1)
            {
                c[x]=1;
                y=x;
                x=perm[x];
                if(c[x]==2)
                    break;
                if(c[x]==1)
                {
                    if(x==y)
                        break;
                    adj[x][y]=0;
                    adj[y][x]=0;
                    break;
                }
            }
            x=i;
            while(1)
            {
                if(c[x]==2)
                    break;
                c[x]=2;
                x=perm[x];
            }
        }
        for(i=1;i<=n;i++)
        {
            c[i]=0;
        }
        for(i=1;i<=n;i++)
        {
            for(j=1;j<i;j++)
            {
                if(adj[i][j]==1)
                {
                    v[i].push_back(j);
                    v[j].push_back(i);
                    h[i]++;
                    h[j]++;
                    p.push_back({i,j});
                }
            }
        }
        for(i=1;i<=n;i++)
        {
            if(c[i]==0)
            {
                u.push_back(f(i,0));
            }
        }
        for(i=0;i<u.size()-1;i++)
        {
            x=u[i].first;
            y=u[i+1].second;
            v[x].push_back(y);
            v[y].push_back(x);
            h[x]++;
            h[y]++;
            p.push_back({x,y});
        }
    return p;
}
};
vector<pair<int,int>> Alice()
{
    return A::Alice();
}
