/*************************************************************************
	> File Name: spfa.cpp
	> Author: YeGuoSheng
	> Description:  
	> Created Time: 2019年07月19日 星期五 09时21分31秒
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
const int maxn = 1000;
const int INF = 0x3f3f3f3f;

int vis[maxn];
int cnt[maxn];
int n;
int m;

struct node
{
    int to;  
    int w;
    int next;
}edges[maxn];
int head[maxn],edge;
int dis[maxn];

void ini()
{
    fill(head,head+maxn,-1);
    edge=0;
}
void addedge(int u,int v,int w)
{
    edges[edge].to=v;
    edges[edge].w=w;
    edges[edge].next=head[u];
    head[u]=edge++;
}
int SPFA(int s,int t)
{
    memset(dis,INF,sizeof(dis));
    memset(vis,false,sizeof(vis));
    queue<int>que;
    dis[s]=0;
    vis[s]=true;
    que.push(s);
    while(!que.empty())
    {
        int u=que.front();
        que.pop();
        vis[u]=false;
        for(int i=head[u];i!=-1;i=edges[i].next)
        {
            int v=edges[i].to;
            int w=edges[i].w;
            if(dis[v]>dis[u]+w)
            {
                dis[v]=dis[u]+w;
                if(!vis[v])
                {
                    vis[v]=true;
                    que.push(v);
                }
                //if(++cnt[v] >=n)
                //{
                //  return true;
                //}
                //
                //
            }
        }
    }
    return dis[t];
}
int main()
{
    return 0;
}
