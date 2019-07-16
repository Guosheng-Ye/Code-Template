// 关于LCA离线算法的理解，请参照：http://www.cnblogs.com/JVxie/p/4854719.html


#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

struct VerInfo
{
	//string data;
	vector<int> arcs;
};

class CommonAncestors
{
protected:
	int n; //总共有n个结点
	int* parent;// parent[i]表示i的父节点
	VerInfo *gra; //邻接表
	bool *visit; //visit[i]表示第i个顶点是否已被访问
	int root;
	void Init();
	int Find(int x);
	void Union(int x, int y);
	void LCA(int r, int u, int v, int& ca);
	int LCA(int u, int v);
public:
	void Solve();
};

void CommonAncestors::Init()
{
	root = 0;

	while (parent[root] >= 0)
	{
		root = parent[root];
	}//初始化，找到根结点结束

	for (int i = 0; i < n; i++)
	{
		parent[i] = i;//所有的结点parent为自己
	}

	fill(visit, visit + n, false);//开始结点都未访问
}

int CommonAncestors::Find(int x)
{
	if (x != parent[x])
	{
		parent[x] = Find(parent[x]);//路径压缩 找根
	}
	return parent[x];//
}

void CommonAncestors::Union(int x, int y)//儿子合并到根结点
{
	x = Find(x);
	y = Find(y);
	if (x == y)
	{
		return;
	}
	parent[y] = x;
}

void CommonAncestors::LCA(int r, int u, int v, int& ca)
{
	for (vector<int>::iterator i = gra[r].arcs.begin(); i != gra[r].arcs.end(); i++)
	{
		if (visit[*i])
		{
			continue;
		}
		//*i未访问
		LCA(*i, u, v, ca);//ca为根结点
		Union(r, *i);//合并到父亲结点
	}
	visit[r] = true;//父亲结点所有的孩子都访问过
	if (r == u && visit[v] == true)
	{
		ca = Find(v);
	}
	else if (r == v && visit[u] == true)
	{
		ca = Find(u);
	}
}

int CommonAncestors::LCA(int u, int v)
{
	Init();
	int ans = -1;
	LCA(root, u, v, ans);
	return ans;
}

void CommonAncestors::Solve()
{
	scanf("%d", &n);
	gra = new VerInfo[n];
	visit = new bool[n];
	parent = new int[n];
	fill(parent, parent + n, -1);
	for (int i = 0; i < n - 1; i++)
	{
		int a = 0, b = 0;
		scanf("%d %d", &a, &b);
		gra[a - 1].arcs.push_back(b - 1);//孩子结点添加到邻接表中
		parent[b - 1] = a - 1;
	}
	int u = 0, v = 0;
	scanf("%d %d", &u, &v);
	int ans = LCA(u - 1, v - 1);
	printf("%d\n", ans + 1);
	for (int i = 0; i < n; i++)
	{
		gra[i].arcs.clear();
	}
	delete[] parent;
	delete[] visit;
	delete[] gra;
}

int main()
{
	int t = 0;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		CommonAncestors obj;
		obj.Solve();
	}
	return 0;
}
