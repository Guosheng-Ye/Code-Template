/*************************************************************************
	> File Name: floyed.cpp
	> Author: YeGuoSheng
	> Description:  
	> Created Time: 2019年07月19日 星期五 06时48分42秒
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
const  int maxn = 20;
const int INF = 0x3f3f3f3f;

int n;
int arr[maxn][maxn];
int path[maxn][maxn];
int Graph[maxn][maxn];

void Floyed()
{
    for(int i = 0 ;i < n ;i++)
    {
        for(int j = 0 ; j< n;j++)
        {
            arr[i][j] = Graph[i][j];
            if(i !=j && Graph[i][j] <INF) 
            {
                path[i][j] = i;
            }
            else
            {
                path[i][j] = -1;
            }
        }
    }
    //初始化完成
    for(int k = 0 ; k  <n;k++)//中间结点    i -> k -> j
    {
        for(int i = 0 ; i < n;i++)
        {
            for(int j = 0 ;j < n;j++)
            {
                if(arr[i][j] > arr[i][k] + arr[k][j])
                {
                    arr[i][j] = arr[i][k] + arr[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}


int main()
{
 
    return 0;
}
