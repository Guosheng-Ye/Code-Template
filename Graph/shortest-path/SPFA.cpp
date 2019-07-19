/*************************************************************************
	> File Name: SPFA链式.cpp
	> Author: YeGuoSheng
	> Description:  
	> Created Time: 2019年07月20日 星期六 07时09分05秒
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
const int maxn=10005;
const int inf = 0x3f3f3f3f;
int head[maxn];   //head[u]表示以head为出发点的邻接表表头在数组Node中的位置，开始时所有元素初始化为-1
int d[maxn];      //记录起点到个点的最短距离
bool vis[maxn];   //标记数组是否进入队列
int n,m,cnt;

struct node
{
    int v;    //所存路径的终点
    int w;    //权值
    int next;     //（重点）与当前所存路径同起点的上一条路径
}Node[maxn];

void add(int u,int v,int w)  //链式前向星存图
{
    Node[cnt].v=v;
    Node[cnt].w=w;
    Node[cnt].next=head[u];
    head[u]=cnt++;
}
void spfa(int x)
{
    memset(vis,0,sizeof(vis));
    memset(d,inf,sizeof(d));
    queue<int>q;
    vis[x]=1;
    d[x]=0;    //x为原点
    q.push(x);
    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        vis[t]=0;            //记得取消标记  与BFS不同
        for(int i=head[t];i!=-1;i=Node[i].next)   //直到以t为起点的路径全部加入队列才结束这一次的 for 循环（也就是直到找到第一个被输入的项，其next值为-1）
        {
            node e = Node[i];
            if(d[e.v]>d[t]+e.w)      //松弛操作
            {
                d[e.v]=d[t]+e.w;
                if(!vis[e.v])        //若被搜索到的节点不在队列q中，则把 e.v 加入到队列中
                {
                    q.push(e.v);
                    vis[e.v]=1;
                }
            }
        }
    }
}

int main()
{
	 while(cin>>n>>m)
	    {
		for(int i = 1 ;i<=n;i++)
		{
		    head[i] = -1;
		    for(int j = 1; j<= m;j++)
		    {
			int a,b ,w;
			cin>>a>>b>>w;
			Node[i].v = a;
			Node[i].w = w;
			Node[i].next = head[a];
			head[a] = i;
		    }
		}
	    }
    return 0;
}
