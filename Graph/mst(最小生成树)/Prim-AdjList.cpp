/*************************************************************************
	> File Name: p3366.cpp
	> Author: YeGuoSheng
	> Description: 
最小生成树模板 、如题，给出一个无向图，求出最小生成树，如果该图不连通，则输出orz
输入格式
第一行包含两个整数N、M，表示该图共有N个结点和M条无向边。（N<=5000，M<=200000）

接下来M行每行包含三个整数Xi、Yi、Zi，表示有一条长度为Zi的无向边连接结点Xi、Yi

输出格式
输出包含一个数，即最小生成树的各边的长度之和；如果该图不连通则输出orz
输入输出样例
输入 #1 复制
4 5
1 2 2
1 3 2
1 4 3
2 3 4
3 4 3
输出 #1 复制
7
	> Created Time: 2019年08月02日 星期五 10时26分54秒
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
const int maxn = 500005;
const int INF = 0x3f3f3f3f;
int head[maxn];
int dis[maxn];
int vis[maxn];
int n,m;//顶点数，边数
struct edge
{
    int v;
    int w;
    int next;
}edges[maxn<<1];

int cnt = 1;

void Add(int x,int y,int w)
{
   edges[cnt].v = y;
   edges[cnt].w = w;
   edges[cnt].next = head[x];
   head[x] = cnt ++;
}   

void Init()
{
    cin>>n>>m;
    int x,y,w;
    for(int i = 1;i <= m;i++)
    {

        cin>>x>>y>>w;
        Add(x,y,w);//添加双向边
        Add(y,x,w);
    }
}

void Prim()
{
    int total = 0;
    int ans = 0;
    int now = 1;
    for(int i = 2;i <= n;i++)
    {
        dis[i] = INF;
    }

    for(int i = head[1];i;i=edges[i].next)
    {
        dis[edges[i].v] = min(dis[edges[i].v],edges[i].w);
    }//更新所有与起点1相连的边并找到最小值

    while(++total < n)//加入mst顶点数<图的顶点数即没找完，循环
    {
        int minn = INF;
        vis[now] = 1;
        for(int i = 1;i <= n;i++)
        {
            if (! vis[i] && minn > dis[i])//找到一条最短边
            {
                minn = dis[i];
                now = i;
            }
        }
        ans += minn;//当前找到的最短距离加入结果距离变量中
        for(int i = head[now]; i ; i =edges[i].next)//松弛操作
        {
            int v = edges[i].v;
            if(  ! vis[v]&& dis[v] > edges[i].w )
            {
                dis[v] = edges[i].w;
            }
        }
    }
    if(ans < INF)//找到解
    {
       cout<<ans<<endl;
    }
    else
    {
        cout<<"orz"<<endl;
    }
    
}
int main()
{
    Init();
    Prim();
    return 0;
}
