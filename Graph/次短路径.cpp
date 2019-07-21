/*************************************************************************
	> File Name: poj3255.cpp
	> Author: YeGuoSheng
	> Description: 
    给定n个点和需要到达的点编号
    问从1号点到目标点的次短路径(比最短路径长一点的路径长度) 
	> Created Time: 2019年07月21日 星期日 16时40分46秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<cstring>
#include<cmath>
#include<stack>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<string>
#include<algorithm>
#include<iomanip>
#define INF 0x3f3f3f3f
#define MAXN 50010

struct node
{
    int v;
    int next;
    int w;
}edges[MAXN<<2];

int head[MAXN];
int cnt;
int dis[MAXN][2];//dist [i][0]：1 最短路径 ,dist[i][1]次短路径
bool vis[MAXN][2];//vis[i][0]：1 表示到结点i的最短路径已找到，vis[i][1]表示到结点i的次短路径已找到
int n,m;

void add(int u,int v,int w)//链式向前星存储
{
    edges[++cnt].v=v;
    edges[cnt].w=w;
    edges[cnt].next=head[u];
    head[u]=cnt;
}

void dijkstra(int s)
{
    for(int i=0;i <= n;i++)
    {
        dis[i][0]=dis[i][1]= INF;//dist [i][0] 最短路径 ,dist[i][1]次短路径
        vis[i][0]=vis[i][1]= 0;
    }
    dis[s][0] = 0;
    for(int i = 1;i < n*2;i++)
    {
        int MIN = INF;
        int k = 0;
        int flag = 0;
        for(int j = 1;j <= n;j++)
        {
            if(!vis[j][0] && dis[j][0] < MIN)
            {
                MIN=dis[j][0];//找到最小边 将点标记
                k=j;
                flag = 0;
            }
            else if(!vis[j][1] && dis[j][1] <  MIN)//否则找到的就是次短边
            {
                MIN=dis[j][1];
                k=j;
                flag = 1;
            }
        }
        if(MIN == INF)break;//没找到 最短或次短路径
        vis[k][flag]=1;//标记到结点k的最小边或次短边已经找到
        for(int j=  head[k];j!=-1;j=edges[j].next)
        {
            int v = edges[j].v;//第j条边的终点
            int w = edges[j].w;//这条边的权重
            if(MIN+w <= dis[v][0])//小于最短边，更新最短边，同时最短边变为次短边
            {
                dis[v][1] = dis[v][0];//既然dis[v][0]有更小的，那么我先把原来的赋值给dis[v][1]
                dis[v][0] = MIN+w;
            }
            else if(MIN+w <= dis[v][1])//如果大于最短边，小于次短边，根新次短边
            { 
                dis[v][1] = MIN+w;
            }
        }
    }
}
int main()
{
    memset(head,-1,sizeof(head));
    cnt = 0;
    scanf("%d%d",&n,&m);// n:目标结点, m：边的数幂
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);
    }
    dijkstra(1);
    printf("%d\n",dis[n][1]);
    return 0;
}

