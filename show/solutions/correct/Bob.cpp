#include"Bob.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
namespace B{
const ll mod=4096;
ll n,i,j,k,l,r,x,y,z,w,s,t,a[1100000],b[1100000],adj[5500][5500],c[1100000],d[1100000],h[1100000],e,m,perm[1100000];
vector<ll> v[1100000];
vector<pair<ll,ll>> u,p;
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
ll Bob(vector<pair<int,int>> V)
{
   Clear();
    m=V.size();
    for(i=1;i<=m;i++)
    {
        x=V[i-1].first;
        y=V[i-1].second;
        v[x].push_back(y);
        v[y].push_back(x);
        h[x]++;
        h[y]++;
    }
    n=4991;
    for(e=1;e<=31;e++)
    {
        if(e!=31)
        {
            l=(e-1)*161+1;
            r=e*161;
        }
        else
        {
            l=(e-1)*161+1;
            r=4991;
        }
        for(i=1;i<=n;i++)
        {
            if(h[i]>=2)
            {
                //printf("(%lld)\n",i);
                s=0;
                for(j=0;j<h[i];j++)
                {
                    if(l<=v[i][j]&&r>=v[i][j])
                        s++;
                }
                if(s>=2)
                {
                    b[e]=i-1;
                    //printf("%lld %lld\n",e,i-1);
                    break;
                }
            }
            if(i==n)
            {
                b[e]=-1;
            }
        }
    }
    b[0]=0;
    d[1]=1;
    d[2]=2;
    d[4]=3;
    d[8]=4;
    d[16]=5;
    for(i=0;i<=31;i++)
    {
        for(j=0;j<=31;j++)
        {
            if((i|j)==j&&d[(j-i)]!=0)
            {
                if(b[i]!=-1&&b[j]!=-1)
                {
                    a[d[j-i]]=b[i]^b[j];
                }
            }
        }
    }
    s=0;
    for(i=5;i>=1;i--)
    {
        s=s*mod+a[i];
    }
    return s;
}
};
ll Bob(vector<pair<int,int>> V)
{
   return B::Bob(V);
}
