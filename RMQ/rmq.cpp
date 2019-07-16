/*************************************************************************
	> File Name: RMQ.cpp
	> Author: YeGuoSheng
	> Description:  求解区间最值问题
	> Created Time: 2019年07月06日 星期六 19时49分38秒
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
#define MAX 500005
int arr[MAX] ;
int n;	
int num;
int f[MAX][20];
int v[MAX][20];

void Init()
{
	for(int i = 1;i <= n; i++)
	{
		f[i][0] = arr[i];//存放最大，从i开始，长度为2^0距离的最大值为自己
		v[i][0] = arr[i];//存放最小
	}
	for(int j = 1; (1<<j)<=n ;j++)//j<=m
	{
		for(int i = 1;i+(1<<j)-1 <=n ;i++)//i的范围受j的跨度的影响
		{	
			v[i][j] = min( v[i][j-1] , v[i+(1<<(j-1))][j-1]);
			f[i][j] = max( f[i][j-1] , f[i+(1<<(j-1))][j-1]);
		}
	}
}


void max_rmq(int n)
{
	for(int i=1;i<=n;i++)
		f[i][0]=arr[i];
	for(int j=1;(1<<j)<=n;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}

void min_rmq(int n)
{
	for(int i=1;i<=n;i++)
		v[i][0]=arr[i];
	for(int j=1;(1<<j)<=n;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			v[i][j]=min(v[i][j-1],v[i+(1<<(j-1))][j-1]);
}

int  RMQ(int l,int r)
{
	int k=(int)(log(l-r+1.0)/log(2.0));
	int Max = max(f[l][k], f[r-(1<<k)+1] [k]);
	int Min = min(v[l][k], f[r-(1<<k)+1] [k]);
	cout<<Max-Min<<endl;
}

int st_max(int a,int b)
{
	int k=(int)(log(b-a+1.0)/log(2.0));
	return max(f[a][k],f[b-(1<<k)+1][k]);
}

int st_min(int a,int b)
{
	int k=(int)(log(b-a+1.0)/log(2.0));
	return min(v[a][k],v[b-(1<<k)+1][k]);
}
int main()
{
	while(cin>>n>>num &&n !=0 && num !=0)
	{
		for(int i =1; i <=n ;i++)
		{
			scanf("%d",&arr[i]);
		}
		//Init();
		max_rmq(n);
		min_rmq(n);
		int l,r;
		for(int i = 0; i< num ;i++)
		{
			scanf("%d%d",&l,&r);
			int u = st_max(l,r);
			int v = st_min(l,r);
			printf("%d\n",u-v);
		}
	}
    return 0;
}
