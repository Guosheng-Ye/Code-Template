/*************************************************************************
	> File Name: poj2503.cpp
	> Author: YeGuoSheng
	> Description: 翻译，简单字典树，叶子结点存放翻译结果就行。查询到就输出
	> Created Time: 2019年07月09日 星期二 14时05分00秒
 ************************************************************************/
/*
dog ogday
cat atcay
pig igpay
froot ootfray
loops oopslay

atcay
ittenkay
oopslay

cat
eh
loops
 */
#include<iostream>
#include<cstdio>
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

struct node
{
    int cnt;
    char c[26];//结点所对应的字符
    struct node *next[26];
    node ()
    {
        cnt = 0;
        memset(next,0,sizeof(next));
    }
};
node * root = NULL;//根结点初始为NULL

void BuildTrie(char *s,char *temp)
{
    node *p  = root;
    node *tmp = NULL;
    int l = strlen(s);
    for(int i = 0;i < l ;i ++)
    {
        if(p->next[s[i]-'a'] == NULL)
        {
            tmp = new node;
            p->next[s[i]-'a'] = tmp;
            
        }
        p  = p->next[s[i]-'a'];
    }
    p->cnt = 1;
    strcpy(p->c,temp);//存放翻译结果
    
}
void Query(char *s)
{
    node *p = root;
    int l = strlen(s);
    for(int i = 0 ;i< l ;i++)
    {
        if(p->next[s[i]-'a'] == NULL)
        {
            printf("eh\n");
            return ;
        }
        p = p->next[s[i]-'a'];
    }
    printf("%s\n",p->c);
    return ;
}

void Del(node * root)
{
    for(int i = 0;i < 26;i++)
    {
        if(root->next[i])
        {
            Del(root->next[i]);
        }
    }
}

int main()
{
    char str[30],s1[15],s2[15];
    root = new node;
    while(gets(str))
    {
        if(str[0] == '\0')
            break;
        sscanf(str,"%s %s",s1,s2);
        BuildTrie(s2,s1);//参数位置
    }
    while(scanf("%s",str)!=EOF)
        Query(str);
    return 0;
}

