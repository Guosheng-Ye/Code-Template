
#define MAXVALUE 9999
#define MAXLEAF 30
#define MAXNODE MAXLEAF*2-1

#include <iostream> 
#include <malloc.h> 
#include <stdio.h> 
#include <stdlib.h>
using namespace std;

typedef struct
{
	int weight;
	int parent;
	int lchild;
	int rchild;
}HTNode;

void HuffmanTree(HTNode HT[], int n)
{
	int i,j,x1,x2;
	int m1,m2;
    for(i=1;i<=n-1;++i)
	{
		m1=m2=MAXVALUE; 
		x1=x2=0;	
		for(j=1;j<n+i;++j)
		{
			if(HT[j].parent==0)
			{	if (HT[j].weight<m1) 
				{	
					m2=m1; 
					x2=x1;
					m1=HT[j].weight; 
					x1=j;
				}
			    else if(HT[j].weight<m2) 
				{
					m2=HT[j].weight; 
					x2=j;
				}
			}
		}
		HT[x1].parent=n+i;
		HT[x2].parent=n+i;
		HT[n+i].weight = HT[x1].weight + HT[x2].weight;
		HT[n+i].lchild=x1;
		HT[n+i].rchild=x2;
	}
}

#define MAXBIT 20
typedef struct
{
	int bit[MAXBIT];
	int start;
}HCodeType;

void HuffmanCode (HTNode HT[], int n, HCodeType HuffCode[])
{
	HCodeType cd; 
	int i,j,c,p;
	for(i=1;i<=n;++i)
	{
		cd.start=n; 
		c=i; 
		p=HT[c].parent;
		while(p!=0)
		{
			if(HT[p].lchild==c) 
				cd.bit[cd.start]=0;
			else 
				cd.bit[cd.start]=1;
			cd.start--;  
			c=p;  
			p=HT[c].parent ;
		}

		for(j=cd.start+1;j<=n;j++) 
		HuffCode[i].bit[j]=cd.bit[j];
		HuffCode[i].start=cd.start;
	}
	for(i=1;i<=n;++i)
	{
		cout<<"The "<<i<<" string---->huffamn code ::";
		for(j=HuffCode[i].start+1;j<=n;j++)
		{
			cout<<HuffCode[i].bit[j];
			//printf("%d",HuffCode[i].bit[j]);
		}
		cout<<endl;
	}
}

int  main()
{
	int n=8;
	HTNode HT[MAXNODE];
	for(int i=1; i<=2*n-1; ++i) //初始化
	{
		HT[i].weight=0; 
		HT[i].parent=0;
		HT[i].lchild=0; 
		HT[i].rchild=0;
	}
	for(int i=1;i<=n;++i)
	{
		cout<<"Please input the "<<i<<"value："<<endl;
		scanf("%d",&HT[i].weight);
		if(HT[i].weight>=MAXVALUE)
		{
			printf("ERROR!INPUT AGAIN\n");
			--i;
		}
	}
	HuffmanTree(HT,n);
	HCodeType HuffCode[MAXNODE];
	HuffmanCode (HT,n,HuffCode);

}