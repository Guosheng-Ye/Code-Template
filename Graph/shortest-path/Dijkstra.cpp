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
const int maxn = 20;
const int INF = 65535;
int Graph[maxn][maxn];
int n;
int m;

void DijkstraPath(int v0,int vis[],int dist[],int path[])
{
    int onePath[maxn];
    int d;
    int k;
    for(int i = 0;i < n;i++)
    {
        if( vis[i] && i != v0)
        {
            cout<<"Path->";
            d = 0;
            onePath[d] = i;//添加路径上的终点
            k = path[i];
            if(k == -1)
            {
                cout<<"No paht"<<endl;
            }
            else
            {
                while(k != v0)
                {
                    d++;
                    onePath[d] = k;
                    k = path[k];
                }
                d++;
                onePath[d] = v0;//添加起点
                cout<<"Start :"<<onePath[d];//起点
                for(int j = d - 1;j>=0;j--)
                {
                    cout<<onePath[j]<<" ";
                }
                cout<<endl;
            }
        }
    }
}

void Dijkstra(int v0)
{
    int dist[maxn];//距离数组，每个点到v0的直接距离
    int path[maxn];//路径数组，记录最短路径上的前驱结点
    int vis[maxn];
    int u;//中间结点
    memset(dist,0,sizeof(dist));
    memset(path,0,sizeof(path));
    memset(vis,0,sizeof(vis));
    int mindist;
    for(int i = 0;i < n;i++)
    {
        dist[i] = Graph[v0][i];
        if(Graph[v0][i] < INF)
        {
            path[i] = v0;//开始与v0直连的点记录
        }
        else
        {
            path[i] = -1;
        }
    }
    vis[v0] = 1;//开始时v0加入最短路中
    path[v0] = 0;
    for(int i = 0; i < n-1;i++)
    {
        mindist = INF;
        for(int j = 0;j < n;j++)
        {
            if( !(vis[i]) && dist[j] < mindist)//找最短路
            {
                mindist = dist[j];
                u = j;
            }
        }
        vis[u] = 1;
        for(int i = 0 ; i < n;i++)//路径更新
        {
            if( !(vis[i]))////考虑剩下未访问的边
            {
                if( Graph[u][i] < INF && dist[i] > dist[u] + Graph[u][i] )
                //中间点的总路程比原来能直达的更短
                {
                    dist[i] = dist[u] + Graph[u][i];
                    path[i] = u;//更新前驱结点
                }
            }
        }
    }
    DijkstraPath( v0, vis,dist,path);//输入最短路径
}

int main()
{
    return 0;
}
