struct Node
{
	int data;	//结点对应顶点编号
	int rank;	//结点对应秩（并查集树的深度）
	int parent;	//结点对应双亲下标
	int relation; //与父节点的关系
};		//并查集树的结点类型

class UFS 
{
protected:
	int n; 
	Node* tree; 
public:
	UFS(int n); // 构造方法，初始化
	~UFS(); // 析构方法
	void Init(); // 初始化
	int Find(int x); // 查找x的代表元素（根），查找的同时进行路径压缩
	void Union(int x, int y); // 合并x和y，x和y之间的可能有d种
};

// 构造方法，初始化
UFS::UFS(int n)
{
	this->n = n;
	tree = new Node[n];
	Init();
}

// 析构方法
UFS::~UFS()
{
	delete[] tree;
}

void UFS::Init()
{
	for (int i = 0; i < n; i++)			//顶点编号为0～(n-1)
	{
		tree[i].rank = 0;			//秩初始化为0
		tree[i].parent = i;		//双亲初始化指向自已
		tree[i].relation = 0;	//i自己是一类，它的父节点此时就是它自己，属于同一类
	}
}

// 查找x的代表元素（根），查找的同时进行路径压缩
int UFS::Find(int x)
{
	int temp = tree[x].parent; // 将x父节点的下标存入temp
	if (x != tree[x].parent)		//若双亲不是自已
	{
		tree[x].parent = Find(tree[x].parent);//递归在双亲中找x
		return tree[x].parent; // 返回根节点下标
	}
	else
	{
		return x;			//若双亲是自已,返回x
	}
}

// 合并x和y
void UFS::Union(int x, int y)
{
	int rootx = Find(x); // 找到下标为x的元素的根节点下标rootx
	int rooty = Find(y); // 找到下标为y的元素的根节点下标rooty
	if (rootx == rooty) // 已合并，还搞个毛，直接返回
	{
		return;
	}

	if (tree[rootx].rank > tree[rooty].rank)	//rooty结点的秩（深度）小于rootx结点的秩
	{
		tree[rooty].parent = rootx;	//将rooty连到rootx结点上,rootx作为rooty的孩子结点
	}
	else	//rooty结点的秩大于等于rootx结点的秩
	{
		tree[rootx].parent = rooty;	//将rootx连到rooty结点上,rooty作为rootx的孩子结点
		if (tree[rootx].rank == tree[rooty].rank)	//rootx和rooty结点的秩（深度）相同
		{
			tree[rooty].rank++;		//rooty结点的秩增1
		}
	}
}
