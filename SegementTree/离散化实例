/*
假设给你一个长度为11的数列:1 2 2 3 4 7 6 5 5 2 5
要求变成一个数列为：  1 2 3 4 5 6 7     （那么这个过程就是离散化）
*/
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
int main()
{
    int arr[12];
    for(int i=0;i<11;i++)
    {
        cin>>arr[i];
    }
    //第一步：排序
    sort(arr,arr+11);//默认从小到大排序
    //第二步：去重
    int tot=unique(arr,arr+11)-arr;//得到一个去重后的数列
    /*
    unique();这个函数是STL里面自带的一个去重函数
    一般参数：
    unique(参数1,参数2);
    参数1：代表数组首地址
    参数2：代表数组末地址
    返回值为末地址
    所以我们减首地址就得到了去重后的元素个数
    */
    cout<<"去重后的数组:"<<endl;
    for(int i=0;i<tot;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}
