#include <cstdio>
#include <iostream>
#include <cstdlib>

typedef int item;
using namespace std;

class NODE
{
  item data;
  NODE *left;
  NODE *right;
public:
  NODE(item data, NODE *left=NULL, NODE *right=NULL):data(data),left(left),right(right){}
  void show(){cout<<data<<endl;}
  void modify(int);
  friend class BST;
};

class BST
{
  NODE *root;
  int count;
public:
  BST():root(NULL),count(0){}
  void insert(NODE* root, item data)
  {
    NODE *newnode=new NODE(data);
    if(root==NULL) root=newnode;
    else if(data<root->left)
      {
	root->left=insert()
      }
  }
  void inorder(){}
  void preorder(){}
  void postorder(){}
}
/**********************************************************************/
void NODE::modify(item newData)
{
  data=newData;
}
int main()
{
  NODE *head;
  head= new NODE(1);
  head->show();
  head->modify(5);
  head->show();
  cout<<endl;return 0;
}
