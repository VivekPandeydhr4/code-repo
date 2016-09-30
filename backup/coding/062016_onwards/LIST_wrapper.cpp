#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;
/***************************************************************/
typedef struct node{
  int data;
  struct node *next;
}NODE;
NODE* create_list(int *A, int n)
{
  int i;
  NODE *head, *newnode, *tail;
  head=tail=NULL;
  for(i=0;i<n;i++)
    {
      newnode=(NODE*)malloc(sizeof(NODE));
      newnode->data=A[i];
      newnode->next=NULL;
      if(!head)  head=tail=newnode;
      else{
	tail->next=newnode;
	tail=newnode;
      }
    }
  return head;
}
void print_list(NODE *head)
{
  NODE *temp;
  temp=head;
  while(temp){
    cout<< temp->data<<' ';
    temp=temp->next;
  }
  cout<<endl;
}
/***************************************************************/

/***************************************************************/
int main()
{
  NODE* head;
  int n, A[]={1,2,3,4,5,6,7,8};
  n=sizeof(A)/sizeof(A[0]);
  head=create_list(A,n);
  print_list(head);
  cout <<endl; return 0;
}
