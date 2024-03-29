/*************************************************************************
	> File Name: prim.cpp
	> Author: YeGuoSheng
	> Description:  与Dijkstra算法思想类似，贪心的选择最短边
	> Created Time: 2019年07月18日 星期四 08时49分49秒
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
const int INF = 0x3f3f3f3f;
const int maxn = 10001;
int Graph[maxn][maxn];
int lowcost[maxn];//与生成树中相连边的最小边
bool vetSet[maxn];//标记结点是否在生成树中
int n;
int edge;


void Create()
{
	for(int i = 0; i< n;i++)
	{
		for(int j = 0 ; j< n;j++)
		{
			Graph[i][j] = 0;
		}
	}
	for(int i = 0; i< edge;i++)
	{
		int a,b,w;
		cin>>a>>b>>w;
		Graph[a][b] = Graph[b][a] = w;
	}
}

void Prim(int n,int v0,int & sum)
{
	int v,k;
	int mindist;
	for(int i = 0; i < n ;i++)
	{
		lowcost[i] = Graph[v0][i];//初值为各顶点v0之间的距离
		vetSet[i] = false;
	}	
	v = v0;
	sum = 0;
	vetSet[v] = true;
	for(int i = 0; i < n;i++)
	{
		mindist = INF;
		for(int j = 0;j < n;j++)
		{
			if((!vetSet[j]) && lowcost[j] < mindist)//找到当前要加入生成树的最小的边
			{
				mindist = lowcost[j];//更新min
				k = j;//记录结点编号
			}
		}
		vetSet[k] = true;
		sum += min;
		for(int j = 0; j < n;j++)//松弛操作
		{
			if( (!vetSet[j]) && lowcost[j] > Graph[v][j])
			{
				lowcost[j] = Graph[v][j];
			}
		}
	}
}

int main()
{
	
	cin>>n>>edge;
	int sum =0 ;
	Create();
	Prim(n,1,sum);
	cout<<sum;
    return 0;
}
