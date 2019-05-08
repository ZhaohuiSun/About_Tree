#include<iostream>
#include<stack>
#include<queue>
#include<fstream>
#include<cstdlib>
using namespace std;



//定义节点
typedef struct node
{
	struct node *lchild;
	struct node *rchild;
	char data;
}BiTreeNode, *BiTree;


//按照前序顺序建立二叉树
void createBiTree(BiTree &T) //&的意思是传进来节点指针的引用，括号内等价于 BiTreeNode* &T,目的是让传递进来的指针发生改变
{
	
	char c;
	cin >> c;
	if ('#' == c)             //当遇到#时，令树的根节点为NULL，从而结束该分支的递归
		T = NULL;
	else
	{
		T = new BiTreeNode;
		T->data = c;
		createBiTree(T->lchild);
		createBiTree(T->rchild);
	}
}

//前序遍历二叉树并打印
void preTraverse(BiTree T)
{
	stack<BiTreeNode*> s;
	BiTreeNode* p = T;
	while (p || !s.empty())
	{
		if (p)
		{
			cout << p->data << ' ';
			s.push(p);
			p = p->lchild;
		}
		else
		{
			p = s.top()->rchild;
			s.pop();
		}
	}
}
//中序遍历二叉树并打印
void midTraverse(BiTree T)
{
	stack<BiTreeNode*> s;
	BiTreeNode* p = T;
	while (p || !s.empty())
	{
		if (p)
		{
			s.push(p);
			p = p->lchild;
		}
		else
		{
			cout << s.top()->data << ' ';
			p = s.top()->rchild;
			s.pop();
		}
	}
}
//后续遍历二叉树并打印
void postTraverse(BiTree T)
{
	BiTreeNode* pre = nullptr;
	BiTreeNode* cur = T;
	stack<BiTreeNode*> s;
	s.push(cur);
	while (!s.empty())
	{
		cur = s.top();
		if ((!cur->lchild && !cur->rchild) || pre &&((pre == cur->lchild || pre == cur->rchild)))
		{										// 确保可以正确输出第一个节点(例如：在左斜树中，pre初始化就是NULL，
											    // cur指向的第一个节点的right指针也是NULL，只判断pre==cur->right的话就会直接输出根节点)。
			cout << cur->data << ' ';
			pre = cur;
			s.pop();
		}
		else
		{
			if (cur->rchild)               //先入栈右节点，再入左节点，出站在前面的才是左节点
				s.push(cur->rchild);
			if (cur->lchild)
				s.push(cur->lchild);
		}
	}
}
void LevelOrder(BiTree T)
{
	BiTreeNode* p=T;
	queue<BiTreeNode*> q;
	q.push(p);
	while (!q.empty())
	{
		p = q.front();
		cout << p->data << ' ';
		q.pop();
		if (p->lchild != NULL)
			q.push(p->lchild);
		if (p->rchild != NULL)
			q.push(p->rchild);
	}

}
int CountNodes(BiTree T)
{
	if (T == NULL)
		return 0;
	return CountNodes(T->lchild) + CountNodes(T->rchild) + 1;

	//非递归方法可通过前序遍历实现

}


BiTreeNode* FindLCA(BiTree T, BiTreeNode * target1, BiTreeNode * target2)  //求两个节点的最低公共祖先节点
{
	if (T == nullptr)
		return nullptr;
	if (T == target1 || T == target2)
		return T;
	BiTreeNode * left = FindLCA(T->lchild, target1, target2);
	BiTreeNode * right = FindLCA(T->rchild, target1, target2);
	if (left && right)  //分别在左右子树
		return T;
	return left ? left : right;  //都在左子树或右子树
}

int GetDepth(BiTree T,BiTreeNode* target)                  //得到树中某一点的深度
{
	if (T == target)
		return 0;
	if (T == NULL)
		return -999999;
	int left_depth = GetDepth(T->lchild, target) + 1;
	int right_depth = GetDepth(T->rchild, target) + 1;
	return left_depth > right_depth ? left_depth : right_depth;
}

void Distance_of_Nodes(BiTree T, BiTreeNode * target1, BiTreeNode* target2)   //求两节点之间的距离转化为先求
{
	BiTreeNode* p = FindLCA(T, target1, target2);							 //最低公共祖先节点，然后求以此节点为根的子树下
	cout << "两个节点之间的距离为：" << GetDepth(p, target1) + GetDepth(p, target2);   //两节点所在深度的和
}

int main()
{

	BiTree T;               //声明一个指向二叉树根节点的指针      
	createBiTree(T);
	cout << "二叉树创建完成！" << endl;
	cout << "前序遍历二叉树：" << endl;
	preTraverse(T);
	cout << endl;
	cout << "中序遍历二叉树：" << endl;
	midTraverse(T);
	cout << endl;
	cout << "后序遍历二叉树：" << endl;
	postTraverse(T);
	cout << endl;
	cout << "层次遍历二叉树：" << endl;
	LevelOrder(T);
	cout << endl;
	cout << "二叉树共有 " << CountNodes(T) << " 个节点";
	cout << endl;

	BiTreeNode * target1=T->rchild->rchild;
	BiTreeNode * target2=T->rchild->lchild->lchild;

	cout<<"测试用例中的公共节点："<<FindLCA(T, target1, target2)->data;
	cout << endl;
	cout << "target2 的深度：" << GetDepth(T, target2);
	cout << endl;
	Distance_of_Nodes(T, target1, target2);
	cout << endl;
	system("pause");
	return 0;
}
