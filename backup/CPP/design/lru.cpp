#include <iostream>
#include <cstdio>
#include <map>
#define buffsize 10
using namespacs std;
/**************************************/
typedef struct node
{
  int  page,box;
  struct node *prev, *next;
}NODE;
typedef struct PAGE
{
  int page;
}PAGE;


char* pageRequest(PAGE *BUFFER, NODE **phead, NODE **ptail, int *psize, map<int, NODE*> *H, int page)
{
  if(page>=0 && page<buffsize)
    {
      if(doesExist(H,page))
	{
	  extractNode(phead,ptail,H[page]);
	  H[page]->prev=(*ptail);(*ptail)=(*ptail->next)=H[page];
	  (*ptail)->next==NULL;
	  return BUFFER[(*ptail)->box];
	}
      else
	{
	  if((*psize)<buffsize-1)
	    {
	      newnode=(NODE*)malloc(sizeof(NODE));
	      newnode->page = page;
	      newnode->box = ++(*size);
	      newnode->next=NULL;
	      BUFFER[newnode->box]=page;
	      if(*phead==NULL) (*ptail)=(*phead)=newnode;
	      else (*ptail)=(*ptail)->next=newnode;
	    }
	  else
	    {
	      temp=(*phead);
	      (*phead)=(*phead)->next;
	      i(*phead==NULL) *ptail=NULL;

	      temp->page=page;temp->next=NULL;
	      BUFFER[temp->box]=page;	      
	      if(*ptail) (*ptail)=(*ptail)->next=temp;
	      else (*phead)=(*ptail)=temp;
	    }
	}


    }
}


/**************************************/
int main()
{
  int page,size=0;
  char BUFFER[buffsize][25];
  map<int , NODE*> H;
  NODE *head=NULL;
  NODE *tail=NULL;

  while(1)
    {
      cout<< "New page request(pageNo) : ";
      cin>>pageNo;
      if(pageNo<0) break;
      else
	{
	  cout<<"pageData: "<<requestPage(BUFFER,&head,&tail,&size,&H,pageNo)<<" contents\n";
	  LRU_dump(head);
	}
    }
  

  cout<<endl;return 0;
}
