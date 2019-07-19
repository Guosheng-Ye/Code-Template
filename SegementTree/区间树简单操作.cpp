#define _CRT_SECURE_NO_WARNINGS
//poj3264
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <stdio.h>
#include <limits.h>
using namespace std;

template<typename Type>
struct Node	// 区间树结点
{
	int l;	// [l,r]表示该节点所代表的区间
	int r;
	Type value; // A[l]到A[r]的累加和
	Type maxv;	// A[l]到A[r]的最大值
	Type minv;	// A[l]到A[r]的最小值
	Type add;
	int Len() const;	// 区间中的长度（包含的整数的个数）
	int Mid() const;	
};
template<typename Type>
int Node<Type>::Len() const
{
	return r - l + 1;
}
template<typename Type>
int Node<Type>::Mid() const
{
	return (l + r) / 2;
}

template<typename Type>
class IntervalTree	// 区间树
{
protected:
	int n;		// 从A[0]到A[n-1]总共有n个元素，注意，n不是指区间树本身有多少个节点
	Node<Type>* tree;	// 存放区间树结点的数组
public:
	IntervalTree(int n);
	~IntervalTree();
	void Build(int v, int l, int r);
	void Add(int v, int l, int r, Type m);
	Type QueryValue(int v, int l, int r);
	void Insert(int r, int i, Type value);
	void QueryMaxAndMin(int v, int l, int r, Type& maxValue, Type& minValue);
};

template<typename Type>
IntervalTree<Type>::IntervalTree(int n)
{
	this->n = n;
	tree = new Node<Type>[n * 4];
}

template<typename Type>
IntervalTree<Type>::~IntervalTree()
{
	delete[] tree;
}

template<typename Type>
void IntervalTree<Type>::Build(int v, int l, int r)
{
	tree[v].l = l;
	tree[v].r = r;
	tree[v].maxv = INT_MIN;
	tree[v].minv = INT_MAX;
	tree[v].add = 0;
	tree[v].value = 0;
	if (l == r)
	{
		return;
	}
	int mid = (l + r) / 2;
	Build(v * 2 + 1, l, mid);
	Build(v * 2 + 2, mid + 1, r);
	tree[v].value = tree[2 * v + 1].value + tree[2 * v + 2].value;
}

template<typename Type>
void IntervalTree<Type>::Add(int v, int l, int r, Type m)
{
	if (tree[v].l == l && tree[v].r == r)
	{
		tree[v].add += m;
		return;
	}
	tree[v].value += m * (r - l + 1);
	int mid = (tree[v].l + tree[v].r) / 2;
	if (r <= mid)
	{
		Add(v * 2 + 1, l, r, m);
	}
	else
	{
		if (l > mid)
		{
			Add(v * 2 + 2, l, r, m);
		}
		else 
		{
			Add(v * 2 + 1, l, mid, m);
			Add(v * 2 + 2, mid + 1, r, m);
		}
	}
}

template<typename Type>
Type IntervalTree<Type>::QueryValue(int v, int l, int r)
{
	if (tree[v].l == l && tree[v].r == r)
	{
		return tree[v].value + (tree[v].r - tree[v].l + 1) * tree[v].add;
	}
	if (tree[v].add != 0)
	{
		tree[v].value += (tree[v].r - tree[v].l + 1) * tree[v].add;
		Add(v * 2 + 1, tree[v].l, tree[v].Mid(), tree[v].add);
		Add(v * 2 + 2, tree[v].Mid() + 1, tree[v].r, tree[v].add);
		
		tree[v].add = 0;
	}
	int mid = tree[v].Mid();
	if (r <= mid)
	{
		return QueryValue(v * 2 + 1, l, r);
	}
	else
	{
		if (l > mid)
		{
			return QueryValue(v * 2 + 2, l, r);
		}
		else
		{
			return QueryValue(v * 2 + 1, l, mid) + QueryValue(v * 2 + 2, mid + 1, r);
		}
	}
}

// 区间树根节点下表为r，在[i,i]这个区间内插入值value
template<typename Type>
void IntervalTree<Type>::Insert(int r, int i, Type value)
{
	if (tree[r].l == i && tree[r].r == i)
	{
		tree[r].value = value;
		tree[r].minv = tree[r].maxv = value;
		return;
	}
	tree[r].minv = min(tree[r].minv, value);
	tree[r].maxv = max(tree[r].maxv, value);
	tree[r].value += value;
	if (i <= tree[r].Mid())
	{
		Insert(2 * r + 1, i, value);
	}
	else//i > mid 在右边
	{
		Insert(2 * r + 2, i, value);
	}
}

// 在以v为根的区间树中，寻找操作区间为[l,r]范围内的最小值和最大值
template<typename Type>
void IntervalTree<Type>::QueryMaxAndMin(int v, int l, int r, Type& maxValue, Type& minValue)
{
	if (tree[v].l == l && tree[v].r == r)
	{
		maxValue = max(maxValue, tree[v].maxv);
		minValue = min(minValue, tree[v].minv);
		return;
	}
	if (r <= tree[v].Mid())
	{
		QueryMaxAndMin(2 * v + 1, l, r, maxValue, minValue);
	}
	else if (l > tree[v].Mid())
	{
		QueryMaxAndMin(2 * v + 2, l, r, maxValue, minValue);
	}
	else
	{
		QueryMaxAndMin(2 * v + 1, l, tree[v].Mid(), maxValue, minValue);
		QueryMaxAndMin(2 * v + 2, tree[v].Mid() + 1, r, maxValue, minValue);
	}
}

int main()
{
	//ifstream cin("Text.txt");
	//freopen("Text.txt", "r", stdin);
	int n = 0, q = 0;
	//while (cin >> n >> q && n > 0 && q > 0)
	while(~scanf("%d%d", &n, &q) && n > 0 && q > 0)
	//scanf("%d%d", &n, &q);
	{
		IntervalTree<int> it(n);
		it.Build(0, 0, n - 1);
		for (int i = 0; i < n; i++)
		{
			int num = 0;
			//cin >> num;
			scanf("%d", &num);
			it.Insert(0, i, num);
		}
		for (int i = 0; i < q; i++)
		{
			int l = 0, r = 0;
			scanf("%d%d", &l, &r);
			l--;
			r--;
			int minv = INT_MAX;
			int maxv = INT_MIN;
			it.QueryMaxAndMin(0, l, r, maxv, minv);
			printf("%d\n", maxv - minv);
		}
	}
	return 0;
}
