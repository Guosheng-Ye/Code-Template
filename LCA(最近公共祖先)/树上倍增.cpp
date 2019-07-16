/*************************************************************************
	> File Name: doubleLca.cpp
	> Author: YeGuoSheng
	> Description:  
	> Created Time: 2019年07月07日 星期日 15时00分02秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<cstring>
#include<cmath>
#include<vector>
#include<stack>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<string>
#include<algorithm>
#include<iomanip>
using namespace std;


const int maxn = 5e+5;
const int bitmax = 20;
int lg[maxn];//log 2n向下取整
vector<int>G[maxn];
int depth[maxn];
int father[maxn][bitmax];

void dfs(int now,int fa)
{
    depth[now] =depth[fa]+1;
    father[now][0]=fa;//自己向上0层的父亲是自己
    for(int j =1;j<=lg[depth[now]]+1;j++)
    {
        father[now][j] = father[father[now][j-1]][j-1];
    }
    for(int i = 0; i < G[now].size();i++)
    {  
        if(G[now][i] != fa)
        {
            dfs(G[now][i],now);
        }
        
    }
}
int LCA(int u,int v)
{
    if(depth[u] < depth[v])
    {
        swap(u,v);
    }
    while(depth[u] != depth[v])
    {
        u = father[u][lg[ depth[u]-depth[v]]]; 
    }
    if(u==v)
    {
        return u;
    }
    for(int j =lg[depth[u]];j>=0;j--)
    {
        if(father[u][j] != father[v][j])
        {
            u = father[u][j];
            v = father[v][j];
        }
    }
    return father[u][0];
}
int main()
{
    lg[0] = -1;
    for(int i = 1  ;i < maxn;i++)
    {
       lg[i] = lg[i>>1] + 1; 
    }
    int n;
    int m;
    int s;
    scanf("%d%d%d",&n,&m,&s);
    int x,y;
    for(int i = 1;i <=n -1;i ++)
    {
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(s,0);
    while(m--)
    {
        scanf("%d%d",&x,&y);
        printf("%d\n",LCA(x,y));
    }
    
    return 0;
}
