#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
/***************************************************/

typedef struct node
{
  char *data;
  struct node *next;
}NODE;


/***************************************************/
int str_pal(NODE *head, NODE **pleft, int *pi)
{
  char *str;
  int j,ret;
  if(head)
    {
      ret = str_pal(head->next, pleft,pi);
      if(ret==1)
	{
	  str=head->data;
	  for(j=strlen(str)-1;j>=0;j--)
	    {
	      if(*pleft == NULL) {cout<<"hi\n";return 0;}
	      if((*pleft)->data[*pi]=='\0')
		{
		  *pleft=(*pleft)->next;
		  *pi=0;
		}
	      if(str[j]==(*pleft)->data[*pi]) {cout<<str[j]<<(*pleft)->data[*pi]<<endl;(*pi)++;}
	      else {cout<<"hi\n";return -1;}
	    }
	  return 1;
	}
      else {cout<<"hi\n";return ret;}
    }
  else return 1;
}
int check_stringPalindrome(NODE *head)
{
  NODE *left;
  int i;
  if(head)
    {
      left=head;
      i=0;
      ret= str_pal(head,&left,&i);
      
      if(ret==1 && left->next==NULL && left->data[i]=='\0') return 1;
      else {cout<<"hi\n";return ret;}
    }
  return 1;
}


/***************************************************/
int main()
{
  NODE *temp,*head=(NODE*)malloc(sizeof(NODE));
  head->data="ab";
  head->next=(NODE*)malloc(sizeof(NODE));
  head->next->data="cde";
  head->next->next=(NODE*)malloc(sizeof(NODE));
  head->next->next->data="ed";
  head->next->next->next=(NODE*)malloc(sizeof(NODE));
  head->next->next->next->data="cba";
  
  for(temp=head;temp;temp=temp->next)
    {
      cout<< temp->data<<endl;
    }

  cout <<check_stringPalindrome(head)<<endl;
  return 0;
}
/***************************************************/
