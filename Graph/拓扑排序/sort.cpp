//拓扑排序
/*给你n个顶点，求拓扑排序
步骤：
1、找到一个入度为0的顶点（该顶点为拓扑排序中的一个点）
2、删除与该顶点相连的边
3、重复上述操作
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
#define MAXN 105
int n;//n个顶点(1-n)
int m;//m边
int map[MAXN][MAXN];//1说明有边，0，没有边
int ans[MAXN];//存放结果
int cnt;//拓扑排序的个数
int in[MAXN];//入度
void tosort()
{
    memset(ans,0,sizeof(ans));
    for(int i=1;i<=n;i++)
    {
        int k=-1;
        for(int j=1;j<=n;j++)//第一步
        {
            if(in[j]==0)
            {
                k=j;
                break;
            }
        }
        in[k]=-1;
        ans[cnt++]=k;
        for(int j=1;j<=n;j++)//第二步
        {
            if(map[k][j])
            {
                map[k][j]=0;
                in[j]--;
            }
        }
    }
    for(int i=0;i<cnt-1;i++)
    {
        printf("%d ",ans[i]);
    }
    printf("%d\n",ans[cnt-1]);
}
int main()
{
    memset(map,0,sizeof(map));
    memset(in,0,sizeof(in));
    cnt=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        while(1)
        {
            int a;
            scanf("%d",&a);
            if(a==0)break;
            map[i][a]=1;
            in[a]++;
        }
    }
    tosort();
    return 0;
}
