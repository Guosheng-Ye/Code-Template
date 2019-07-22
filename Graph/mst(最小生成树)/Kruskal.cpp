/*************************************************************************
	> File Name: poj3277.cpp
	> Author: YeGuoSheng
	> Description:  
	> Created Time: 2019年07月17日 星期三 10时13分06秒
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
const int maxn = 20001;
int n;
int m;

int p[maxn];//结点父亲
int Rank[maxn];//秩

struct edge//存放边信息
{
    int a;
    int b;
    int w;
};
edge arr[maxn];
/*
bool cmp(const edge &a,const edge &b)
{
    return a.w > b.w; //求最大生成树，倒序排序
}
*/
void Init()
{
    for(int i = 0 ;i < n;i++)
    {
        Rank[i] = 0;
        p[i] = i;
    }
}

int find(int x)//查找父亲结点
{
    if(p[x]!= x)
        return p[x] = find(p[x]);
    return x;
}

void UFS(int x, int y) //并查集
{
    x = find(x);
    y = find(y);
    if (x == y) return ;//同一个父亲，即在同一个连通分量中，不合并
    if (Rank[x] < Rank[y]) p[x] = y;
    else 
    {
        p[y] = x;
        if (Rank[x] == Rank[y]) ++Rank[x];
    }
}

int Kruskal()
{
    int sum = 0;//最大路径
    int res = 0;//边的个数
    for(int i=0;i < m;i++)
    {
        edge e = arr[i];
        int fa=find(e.a);
        int fb=find(e.b);
        if(fa!=fb)
        {
            UFS(e.a,e.b);
            sum += e.w;
            ++res;
        }
    }
    if((res +1) != n)return  -1;
    return sum;
}
int main()
{
    while(cin>>n>>m)
    {
        Init();
        for(int i =0 ;i < m;i++)
        {
            int a,b,c;
            cin>>a>>b>>c;
            arr[i] =  (edge){a-1,b-1,c};
        }   
        sort(arr,arr+m,cmp);
        cout<<Kruskal()<<endl;
    }
    return 0;
}
