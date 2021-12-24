//采用区间树实现，参考了https://blog.csdn.net/hubi0952/article/details/52768299
#include <iostream>
#include <cstdlib>
using namespace std;

enum Color{
    RED=0,
    BLACK=1
};  //定义枚举类型，即红黑树结点颜色类型，0表示红色，1表示黑色

typedef struct{     //定义一个表示区间范围的结构体
    int low;
    int high;
}Interval;

typedef struct IntervalNode     //声明红黑树结点
{
    Color color;
    struct IntervalNode *left;
    struct IntervalNode *right;
    struct IntervalNode *parent;
    Interval interval;
    int max;
} Node;

typedef struct{            //定义一个红黑树
    Node *root;            //根节点
    Node *nil;             //哨兵结点,避免讨论结点的边界情况
}RBTree;

//求三个参数中的最大值
int GetMax(int high,int leftMax,int rightMax)
{
    int temp=(leftMax>rightMax)?leftMax:rightMax;
    return (high>temp)?high:temp;
}

//左旋，结点x原来的右子树y旋转成x的父母
void LeftRotate(RBTree * rbTree,Node *x)
{
    if(x->right!=rbTree->nil)
    {
        Node *y=x->right;
        x->right=y->left;
        if(y->left!=rbTree->nil)
        {
            y->left->parent=x;
        }
        y->parent=x->parent;
        if(x->parent==rbTree->nil)    //空树，将y设为根
        {
            rbTree->root=y;
        }
        else if(x==x->parent->left)   //x为左子树，将y放在x父节点的左子树
        {
            x->parent->left=y;
        }
        else
        {
            x->parent->right=y;
        }
        y->left=x;
        x->parent=y;

        //以下为区间树与红黑树左旋调整的差异，即要调整结点max的大小,
        //且必须先计算x的max，在计算y的max
        x->max=GetMax(x->interval.high,x->left->max,x->right->max);
        y->max=GetMax(y->interval.high,y->left->max,y->right->max);
    }
}

//右旋，结点x原来的左子树y旋转成x的父母
void RightRotate(RBTree * rbTree,Node *x)
{
    if(x->left!=rbTree->nil)
    {
        Node *y=x->left;
        x->left=y->right;
        if(y->right!=rbTree->nil)
        {
            y->right->parent=x;
        }

        y->parent=x->parent;
        if(x->parent==rbTree->nil)
        {
            rbTree->root=y;
        }
        else if(x==x->parent->left)
        {
            x->parent->left=y;
        }
        else
        {
            x->parent->right=y;
        }
        y->right=x;
        x->parent=y;

        //以下为区间树与红黑树左旋调整的差异，即要调整结点max的大小
        //且必须先计算x的max，在计算y的max
        x->max=GetMax(x->interval.high,x->left->max,x->right->max);
        y->max=GetMax(y->interval.high,y->left->max,y->right->max);
    }
}

//插入后调整树，以维持红黑树的5条性质
void RBInsertFixUp(RBTree *rbTree,Node *z)
{
    Node *y;      //用于记录z的叔叔结点
    while(z->parent->color==RED)   //因为插入的结点是红色的，所以只可能违背性质4,即假如父结点也是红色的，要做调整
    {
        if(z->parent->parent->left==z->parent)  //如果要插入的结点z是其父结点的左子树
        {
            y=z->parent->parent->right;         // y设置为z的叔父结点
            if(y->color==RED)                   //case 1: y的颜色为红色
            {
                z->parent->parent->color=RED;
                y->color=BLACK;
                z->parent->color=BLACK;
                z=z->parent->parent;
            }
            else
            {
                if(z==z->parent->right)    //case 2: y的颜色为黑色，并且z是z的父母的右结点，则z左旋转
                {
                    z=z->parent;
                    LeftRotate(rbTree,z);
                }
                z->parent->parent->color=RED;     //case 3: 如果y的颜色为黑色，并且z是z的父母的左结点
                z->parent->color=BLACK;
                RightRotate(rbTree,z->parent->parent);
            }
        }
        else    //与前一种情况对称，要插入的结点z是其父结点的右子树,注释略去
        {
            y=z->parent->parent->left;
            if(y->color==RED)
            {
                z->parent->parent->color=RED;
                y->color=BLACK;
                z->parent->color=BLACK;
                z=z->parent->parent;
            }
            else
            {
                if(z->parent->left==z)
                {
                    z=z->parent;
                    RightRotate(rbTree,z);
                }
                z->parent->parent->color=RED;
                z->parent->color=BLACK;
                LeftRotate(rbTree,z->parent->parent);
            }
        }
    }
    rbTree->root->color=BLACK;   //最后如果上升为rbTree的根的话，把根的颜色设为黑色
}

//将interval建为节点插入到区间树T中
Node *IntervalInsert(RBTree *rbTree, int low, int high)
{

    Node *z=new Node;       //new一个Node结点空间
    z->color = RED;          //新插入的color设为红色
    z->interval.low = low;
    z->interval.high = high;
    z->max = high;
    z->left = rbTree->nil;
    z->right = rbTree->nil;
    z->parent = NULL;

    //当根为空时，单独处理，直接插入到根结点中，这里暂不考虑
    //如果树不为空，那么从根节点开始，从上往下查找插入点
    Node *y = rbTree->nil;
    Node *x = rbTree->root;
    while (x != rbTree->nil)
    {
        y = x;
        if (y->max < z->interval.high)
            y->max = z->interval.high;
        if (z->interval.low < x->interval.low)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == rbTree->nil)
        rbTree->root = z;
    else{
        if (z->interval.low < y->interval.low)
            y->left = z;
        else
            y->right = z;
    }
    z->left = rbTree->nil;
    z->right = rbTree->nil;
    z->color = RED;
    RBInsertFixUp(rbTree, z); //插入后对树进行调整
    return z;
}

Node *IntervalSearch(RBTree *rbTree, int low, int high)
{
    Interval i;
    i.low = low;
    i.high = high;
    Node *x=rbTree->root;    //从根开始查找
    while(x!=rbTree->nil&&!(i.low<=x->interval.high&&i.high>=x->interval.low)){
        //若x不等于nil节点且x与interval不重叠，则进行判断
        if(x->left!=rbTree->nil&&x->left->max>=i.low)
            x=x->left;       //到x的左子树中继续查找
        else
            x=x->right;      //左子树必查不到，到右子树查
    }
    return x;    //x=nil或者x与interval重叠
}

//创建区间树
RBTree *Interval_Create()
{
    RBTree *T = new RBTree;
    T->nil = (Node *)malloc(sizeof(Node));
    T->nil->interval.low = 0;
    T->nil->interval.high = 0;
    T->nil->max = 0;
    T->nil->left = T->nil;
    T->nil->right = T->nil;
    T->nil->parent = T->nil;
    T->nil->color = BLACK;
    T->root = T->nil;
    return T;
}

int main()
{
    RBTree *T = Interval_Create();
    int N;
    cin>>N;
    for (int i = 0; i < N; i++){
        int a,b;
        cin>>a>>b;
        if ((IntervalSearch(T,a,b)) != T->nil)
            cout<<-1<<endl;
        else{
            IntervalInsert(T,a,b);
            cout<<0<<endl;
        }
    }
    free(T);
    return 0;
}