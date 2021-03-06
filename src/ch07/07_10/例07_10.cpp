#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include<iostream.h>
#define MAXSIZE 100
typedef struct Node
{ 
    char data;
    struct Node * lchild,*rchild;
}BitNode,*BiTree;
void  CreateBitTree(BiTree *T,char str[]);
void PrintLevel(BiTree T);
void  CreateBitTree(BiTree *T,char str[])
/*利用括号嵌套法建立二叉链表*/
{
    char ch;
    BiTree stack[MAXSIZE];	/*定义栈，用于存放指向二叉树中结点的指针*/
    int top=-1;				/*初始化栈顶指针*/
    int flag,k;
    BitNode *p;
    *T=NULL,k=0;
    ch=str[k];
    while(ch!='\0')			/*如果字符串没有结束*/
    {
        switch(ch)
        {
        case '(':
            stack[++top]=p;
            flag=1;
            break;
        case ')':
            top--;
            break;
        case ',':
            flag=2;
            break;
        default:
            p=(BiTree)malloc(sizeof(BitNode));
            p->data=ch;
            p->lchild=NULL;
            p->rchild=NULL;
            if(*T==NULL)/*如果是第一个结点，表示是根结点*/
                *T=p;
            else
            {
                switch(flag)
                {
                case 1:
                    stack[top]->lchild=p;
                    break;
                case 2:
                    stack[top]->rchild=p;
                    break;
                }
            }
        }
        ch=str[++k];
    }
}
void TreePrint(BiTree T,int level) 
/*按树状打印的二叉树*/ 
{   
    int i;
    if(T==NULL)					/*如果指针为空，返回上一层*/ 
        return;
    TreePrint(T->rchild,level+1);/*打印右子树，并将层次加1*/ 
    for(i=0;i<level;i++)			/*按照递归的层次打印空格*/ 
        printf("   ");
    printf("%c\n",T->data);		/*输出根结点*/ 
    TreePrint(T->lchild,level+1);/*打印左子树，并将层次加1*/ 
}
int BiTreeDepth(BiTree T)
/*计算二叉树的深度*/
{
    if(T == NULL) 
        return 0;
    return     BiTreeDepth(T->lchild)>BiTreeDepth(T->rchild)?1+BiTreeDepth(T->lchild):1+BiTreeDepth(T->rchild);
}
int BiTreeWidth(BiTree T)
//求二叉树T的最大宽度
{
    int front,rear,last,maxw,temp;
    BiTree Q[MAXSIZE]; 	//Q是队列，元素为二叉树结点指针
    BitNode *p;
    if (T==NULL)			//空二叉树宽度为0
        return 0; 
    else 
    {
        front=1;rear=1;last=1;//front队头指针,rear队尾指针, last同层最右结点在队列中的位置
        temp=0;			//temp为当前宽度,
        maxw=0; 			//maxw为最大宽度
        Q[rear]=T; 		//根结点入队列
        while(front<=last) 
        {
            p=Q[front++]; 
            temp++; 		//同层元素数加1
            if (p->lchild!=NULL) 
                Q[++rear]=p->lchild; 	//左子女入队
            if (p->rchild!=NULL) 
                Q[++rear]=p->rchild; 	//右子女入队
            if (front>last) 			//一层结束，
            {
                last=rear; 
                if(temp>maxw) 
                    maxw=temp; 		//last指向下层最右元素, 更新当前最大宽度
                temp=0; 
            }
        }
        return maxw; 
    }
}
void main()
{  
    BiTree T;
    char str[MAXSIZE];
    cout<<"请输入二叉树的广义表形式："<<endl;
    cin>>str;
    cout<<"由广义表形式的字符串构造二叉树："<<endl;
    CreateBitTree(&T,str);
    TreePrint(T,1);
    cout<<"这棵二叉树的高度为:"<<BiTreeDepth(T)<<endl;
    cout<<"这棵二叉树的最大宽度为:"<<BiTreeWidth(T)<<endl;
}