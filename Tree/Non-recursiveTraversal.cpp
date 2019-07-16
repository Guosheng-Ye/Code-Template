#include<iostream>
#include<stdio.h>
#include<malloc.h>
using namespace std;

#define ElemType char
#define MaxSize 100

typedef struct node
{
    ElemType data;
    struct node *lchild;
    struct node *rchild;
}BTNode;

void CreateBTree(BTNode *&b)//手动输入二叉树
{
    b = NULL;
    char ch;
    ch = getchar();
    if(ch == '#')
    {
        b = NULL;
    }
    else
    {
        b = (BTNode *)malloc(sizeof(BTNode));
        b->data = ch;
        CreateBTree(b->lchild);
        CreateBTree(b->rchild);
    }
}

BTNode* FindNode(BTNode *b,ElemType x)//return a Node
{
    BTNode *p;
    if(b == NULL)
    {
        return NULL;
    }
    else if(b->data == x)
    {
        return b;
    }
    else
    {
        p = FindNode(b->lchild,x);
        if(p != NULL)
        {
            return p;
        }
        else
        {
            return FindNode(b->rchild,x);
        }
    }
}

BTNode* LchildNode(BTNode *p)//return p lchild
{
    return p->lchild;
}

BTNode* RchildNode(BTNode *p)//return p rchild
{
    return p->rchild;
}

int BTHeight(BTNode *b)//return BTheigh
{
    int lchildh,rchildh;
    if(b == NULL)
    {
        return (0);
    }
    else
    {
        lchildh = BTHeight(b->lchild);
        rchildh = BTHeight(b->rchild);
        return (lchildh >rchildh) ? (lchildh + 1): (rchildh + 1);
    }
}

int Level(BTNode *b,ElemType x,int h)//return Level
{
   
    int level;
    if(b == NULL)
    {
        return (0);
    }
    else if(b->data == x)
    {
        return h;
    }
    else
    {
        level = Level(b->lchild,x,h+1);
        if(level != 0)
        {
            return level;
        }
        else
        {
            return (Level(b->rchild,x,h+1));
        }
    }
}

void DispBTree(BTNode *b)
{
    if(b != NULL)
    {
        cout<<" "<<b->data;
        if(b->lchild != NULL || b->rchild !=  NULL)
        {
            cout<<"(";//有孩子结点才输出（
            DispBTree(b->lchild);//扫描左子树
            if(b->rchild != NULL)//有右子树才输出，
            {
                cout<<",";
            }
            DispBTree(b->rchild);//递归处理右子树
            cout<<")";//有孩子结点才输出
        }
    }
}
void  DispLeaf(BTNode *b)//Print All Leaf
{
    if(b != NULL)
    {
        if(b->lchild == NULL && b->rchild == NULL)
        {
            cout<<b->data;
        }
        DispLeaf(b->lchild);//lchild leaf
        DispLeaf(b->rchild);//rhcild leaf 
        
    }
}
void PreOrder(BTNode *b)
{
    BTNode *st[MaxSize];
    BTNode *p;
    int top = -1;
    if(b != NULL)
    {
        top ++;//根结点进栈
        st[top] = b;
        while(top > -1)//不为空循环
        {
            p = st[top];
            top--;
            cout<<p->data;//退栈并访问
            if(p->rchild != NULL)//有右孩子，进栈
            {
                top++;
                st[top] = p->rchild;
            }
            if(p->lchild != NULL)//有左孩子，进栈
            {
                top++;
                st[top] = p->lchild;
            }
        }
        cout<<endl;
    }
}

void InOrder(BTNode *b)
{
    BTNode *st[MaxSize];
    BTNode *p;
    int top = -1;
    if( b != NULL)
    {
        p = b;
        while(top > -1 || p != NULL)
        {
            while( p!= NULL)//p的所有左下结点进栈 不访问
            {
                top++;
                st[top] = p;
                p = p->lchild;
            }
            if(top > -1)
            {
                p = st[top];//出栈p并访问
                top--;
                cout<<p->data;
                p = p->rchild;
            }
        }
        cout<<endl;
    }
}

void PostOrder(BTNode *b)
{
    BTNode *st[MaxSize];
    BTNode *p;
    int top = -1;
    bool flag;//栈指针初值
    if(b != NULL)   
    {
        do
        {
            while(b != NULL)//b所有左下结点进栈
            {
                top++;
                st[top] = b;
                b = b->lchild;
            }
            p = NULL;//p指向当前结点的上一个已经访问的结点
            flag = true;
            while(top != -1 && flag)//flag为真表示正在处理栈顶结点
            {
                b = st[top];//取出栈顶结点
                if(b->rchild == p)//右子树不存在或已被访问。访问
                {
                    cout<<b->data;//访问b
                    top--;
                    p = b;//p指向已被访问结点
                }
                else
                {
                    b = b->rchild;
                    flag = false;//当前处理的不是栈顶结点
                }
            }
        }while(top != -1);
        cout<<endl;
    }
}

void TravLevel(BTNode *b)
{
    BTNode *Qu[MaxSize];//定义环形队列
    int front;
    int rear;
    front = rear = 0;//置为空
    if(b != NULL)
        cout<<b->data;
    rear++;
    Qu[rear] = b;//根结点进栈
    while(front != rear)
    {
        front = (front + 1)% MaxSize;
        b = Qu[front];//出队结点b
        if(b->lchild != NULL)//输出左孩子，并进队
        {
            cout<<b->lchild->data;
            rear =(rear + 1)%MaxSize;
            Qu[rear] = b->lchild;
        }
        if(b->rchild !=NULL)//输出右孩子，并进队
        {
            cout<<b->rchild->data;
            rear = (rear + 1 ) % MaxSize;
            Qu[rear] = b->rchild;
        }
    }
    cout<<endl;
}
void DestoryBTree(BTNode *&b)
{
    if(b != NULL)
    {
        DestoryBTree(b->lchild);
        DestoryBTree(b->rchild);
        free(b);
    }
}

int Nodes(BTNode *b)
{
    int num1;
    int num2;
    if(b == NULL)
    {
        return 0;
    }
    else if(b->lchild == NULL && b->rchild == NULL)
    {
        return 1;
    }
    else
    {
        num1 = Nodes(b->lchild);
        num2 = Nodes(b->rchild);
        return (num1 + num2 + 1);
    }
}

int main()
{
    BTNode *b;
    cout<<"Create "<<endl;
    CreateBTree(b); 
    cout<<"BTree Height is "<< BTHeight(b)<<endl;
    //~~~~Order!~~~
    cout<<"非递归先序遍历 ->  ";
    PreOrder(b);
    cout<<endl;
    cout<<"非递归中序遍历 ->  ";
    InOrder(b);
    cout<<endl;
    cout<<"非递归后序遍历 ->  ";
    PostOrder(b);
    cout<<endl;
    cout<<"层次     遍历 ->  ";
    TravLevel(b);
    cout<<endl;
    cout<<"Leaf Node-> ";
    DispLeaf(b);
    cout<<endl;
    cout<<"C level is:"<<Level(b,'C',1)<<endl;
    
    cout<<"Free"<<endl;
    DestoryBTree(b);
    return 1;
}   

