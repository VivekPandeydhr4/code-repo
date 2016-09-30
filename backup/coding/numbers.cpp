#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
typedef struct node
{
  int data;
  struct node *next;
}NODE;
using namespace std;
/*************************************/
void print_integer(NODE *head)
{
  if(head)
    {
      print_integer(head->next);
      cout<<head->data;
    }
}
NODE* get_integer()
{
  char c;
  NODE *head=NULL,*newnode;
  while((c=getchar())!=' ' && c!='\n')
    {
      if(c>=48 && c<=57)
	{
	  newnode=(NODE*)malloc(sizeof(NODE));
	  newnode->data=c-'0';
	  newnode->next=head;
	  head=newnode;
	}
      else {cout<<"Invalid input!\n";return NULL;}
    }
  return head;

}
NODE* multiply(NODE *int1, NODE *int2)
{
  NODE *result=NULL;
  for(temp=int1;temp;temp=temp>next)
    {
      newnode=(NODE*)malloc(sizeof(NODE));
      newnode->data==temp->data;newnode->next=NULL;
      if(result==NULL){result=newnode;current=result;}
      else{current->next=newnode;current=newnode;}
    }
  


}
int main()
{
  NODE *integer1=NULL,*integer2=NULL;
  cout<<"Enter 1st integer:";
  integer1=get_integer();  print_integer(integer1);
  // cout<<"Enter 2nd integer:";
  // integer2=get_integer();  
  // result=product(integer1, integer2);
  // print_integer(result);
  return 0;
}
