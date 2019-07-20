/*************************************************************************
	> File Name: p4779.cpp
	> Author: YeGuoSheng
	> Description:  
	> Created Time: 2019年07月20日 星期六 16时46分11秒
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
const int maxn= 10000002;
int n;
int m;
int p;
int cnt;
int dist[1002];
int head[maxn];//init -1
//存放以i为起点的第一条边存储的位置//以i为起点最后的那个编号
int point[1002];

struct Edge//建图
{
    int v;//edge[i]表示第i条边的终点
    int w;//edge[i]表示第i条边的权值 即 距离
    int nxt;//edge[i]表示与第i条边同起点的下一条边的存储位置(上一条边)
}edge[maxn];

void add(int x,int y,int w)// x -> y == w
{//链式向前星
    edge[++cnt].v = y;
    edge[cnt].w = w;
    edge[cnt].nxt = head[x];
    head[x] = cnt;
}

struct node
{
    int u;
    int d;
    bool operator< (const node& rhs)const
    {
        return d >rhs.d;
    }
};

priority_queue<node> q;
void Dijkstra(int s) 
{  
    for(int i=1;i<=n;i++)
        dist[i]=2147483647;
    dist[s]=0;
    priority_queue<node> Q; 
    Q.push((node){s,0});//开始结点进队
    while (!Q.empty()) 
    {
        node fr = Q.top(); Q.pop();
        int u = fr.u;//2,0
        int d = fr.d;
      //          cout<<"dequeue:u:"<<u<<" d:"<<d<<endl;
      //          cout<<"~~~";
        if (d != dist[u]) continue;//dijkstra中每个点只会出队一次 vis
        for (int i = head[u];i;i=edge[i].nxt) 
        {
       //             cout<<"i =="<<i<<endl;
            int v = edge[i].v;//第i条边的终点
       //             cout<<"edge["<<i<<"].v :"<<v<<" ";
            int w = edge[i].w;
        //             cout<<"edge["<<i<<"].w :"<<w<<" ";
        //             cout<<endl<<"~~~~~~~~~~~"<<endl;
            if (dist[u]+w < dist[v]) 
            {
          //              cout<<"dist["<<v<<"]"<<dist[v]<<" "<<endl;
          //              cout<<"dist["<<u<<"] + w :"<<dist[u]+w<<endl;
          //             cout<<"~~~~~~~~~"<<endl;
                dist[v] = dist[u]+w;
           //          cout<<"dist["<<v<<"] = "<<dist[u]+w<<endl;
            //            cout<<v<<"v,dist["<<v<<"] enqueue"<<endl;
                Q.push((node){v,dist[v]});
            }
        }
    }
}
/*
 4 7 1
 1 2
 2 3
 3 4
 1 3
 4 1
 1 5
 4 5
 */
int main()
{
        cin>>n>>m>>p;
        memset(dist,0,sizeof(dist));
        memset(point,0,sizeof(point));
        memset(head,-1,sizeof(head));
        for(int i=1;i<=m;i++)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z);
        }
        //cout<<"~~~~~~~~~~~~~"<<endl;
        // for(int i = 1;i <= m;i++)
        // {
        //     cout<<"  head["<<i<<"]"<<head[i]<<" ||";
        //     cout<<"edge["<<i<<"] ="<<edge[i].v<<" next"<<edge[i].nxt<<endl;
        // }
        //cout<<"~~~~~~~~~~~~~~~~~~~~~"<<endl;
        Dijkstra(p);//p 到其他点的最小距离
        for(int i = 1;i <=n;i++)
        {
            point[i] += dist[i];//先加上从p回来的距离
          //  cout<<point[i]<<" ";
        }
        // for(int i=1;i<=n;i++) 
        //     printf("%d ",d[i]);
        for(int i =1 ;i <= n;i++)
        {
            if(i == p)continue;
            Dijkstra(i);
            point[i] += dist[p];
        }
        sort(point+1,point+n+1);
       // for(int i = 1; i<= n;i++)
        cout<<point[n]<<endl; 
        
    return 0;
}
