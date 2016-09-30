#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
/*************************************/

void Arrange_pos_neg_alternately(int *A, int n)
{
  int i,j,t,k;
  if(*A && n>1)
    {
      for(i=0;i<n-1;)
	{
	  if(i%2==0 && A[i]>0 || i%2 && A[i]<0) i++;
	  else
	    {
	      j=i+1;
	      if(i%2==0)
		while(j<n && A[j]<0) j++;
	      else
		while(j<n && A[j]>0) j++;
	      if(j==n) break;
	      t=A[j];
	      for(k=j-1;k>=i;k--) A[k+1]=A[k];
	      A[i]=t;
	      i++;
	    }
	}
    }  
}

int find_pivot(int *A, int n)
{
  int s,e,mid;
  
  if(n==1 || A[0]<A[n-1]) return 0;

  s=1,e=n-1;
  while(s<e)
    {
      mid=s+(e-s)/2;
      if(A[mid-1]>A[mid]) return mid;
      else if(A[mid]<A[e]) e=mid-1;
      else s=mid+1;
    }  
}

void comb(char *s, char *C,int r, int i, int b)
{
  int l,k;
  if(b==r) {C[b]='\0';cout <<C<<endl;}
  else
    {
      l=strlen(s);
      for(k=i;k<=l-r+b;k++)
	{
	  C[b]=s[k];
	  comb(s,C,r,k+1,b+1);
	}
    }
}
void combination(char *s, int r)
{
  char *C;
  C=(char*)malloc((r+1)*sizeof(char));
  if(r>0) comb(s,C,r,0,0);
    
}

void permutation(char *s, int b)
{
  int l,t,i;
  l=strlen(s);
  if(b==l) cout<<s<<endl;
  else
    {
      for(i=b;i<l;i++)
	{
	  t=s[b];s[b]=s[i];s[i]=t;
	  permutation(s,b+1);
	  t=s[b];s[b]=s[i];s[i]=t;
	}
    }
}

int index_of_flipping_0_giving_longest_chains_of_1s(int A[], int n)
{
  int i=0,j=0,k=0,zero=0,S,E,Result;

  zero=-1;
  for(i=0,j=0;j<n;j++)
    {
      if(A[j]==0)
	{
	  if(zero==-1) zero=j;
	  else break;
	}
    }
  if(j==n) return zero;
  else {S=i;E=j-1;Result=zero;i=zero+1;zero=j;j++;}
  
  while(1)
    {
      while(j<n && A[j]) j++;
      if(j-1-i > E-S) {S=i;E=j-1;Result=zero;}
      if(j<n)
	{
	  i=zero+1;
	  zero=j;
	  j++;
	}    
      else break;
    }
  return Result;
}
typedef struct list
{
  int data;
  struct list *prev,*next;
}NODE;

/*
void clean_and_append(NODE **Phead, NODE **Ptail, int *A, int i,int k)
{
  NODE *newnode,*temp;
  newnode=(NODE*)malloc(sizeof(NODE));
  newnode->prev=newnode->next=NULL;
  newnode->data=i;
  cout << "hi"<<A[i]<<"\n";

  if(*Phead==NULL)
    {
      *Phead=*Ptail=newnode;     
    }
  else
    {
      if(i-(*Phead)->data>=k)
	{
	  (*Phead)=(*Phead)->next;
	  if(*Phead==NULL) *Ptail=NULL;
	  else {free((*Phead)->prev);(*Phead)->prev=NULL;}
	}

    
      temp=*Ptail;
      while(temp && temp->data <= A[i])
	{
	  temp=temp->prev;
	  if(!temp) break;
	  free(temp->next);
	  temp->next=NULL;
	}    
      if(!temp) {*Phead=*Ptail=newnode;}
      else {temp->next=newnode;newnode->prev=temp;*Ptail=newnode;}
    }

}
void pop_front(NODE **Phead, NODE **Ptail, int *Pj)
{
  NODE *temp;
  
  if(*Phead==NULL) *Pj=-1;
  else
    {
      *Pj=(*Phead)->data;
      temp=(*Phead);
      *Phead=(*Phead)->next;
      if(*Phead==NULL) *Ptail=NULL;
      else (*Phead)->prev=NULL;
      free(temp);
    }
}

*/

void clean_and_append(NODE **Phead,NODE **Ptail, int *A, int i, int k )
{
  NODE *newnode=NULL,*temp=NULL,*temp2=NULL;;
  newnode=(NODE*)malloc(sizeof(NODE));
  newnode->data=i;newnode->prev=newnode->next=NULL;

  if(*Phead==NULL) *Phead=*Ptail=newnode;
  else
    {
      if((*Phead)->data+k<=i)
	{
	  temp=*Phead;
	  *Phead=(*Phead)->next;
	  if(*Phead==NULL) *Ptail=NULL;
	  else (*Phead)->prev=NULL;
	  free(temp);
	}
      for(temp=*Ptail;temp;)
	{
	  if(A[temp->data]>A[i]) break;
	  temp2=temp;
	  temp=temp->prev;
	  if(temp==NULL) *Phead=*Ptail=NULL;
	  else {temp->next=NULL;}
	  free(temp2);
	}
      if(*Ptail==NULL) *Phead=*Ptail=newnode;
      else {temp->next=newnode;newnode->prev=temp;*Ptail=newnode;}
    }
}

void pop_front(NODE **Phead,NODE **Ptail, int *Pj)
{
  NODE *temp=NULL;
  if(*Phead==NULL) *Pj=-1;
  else  *Pj=(*Phead)->data;
  /*{

      temp=*Phead;
      *Phead=(*Phead)->next;
      if(*Phead==NULL) *Ptail=NULL;
      else (*Phead)->prev=NULL;
      free(temp);      
      }*/
}
void Max_in_each_window_of_size_k(int *A, int n, int k)
{
  NODE *head=NULL,*tail=NULL;
  int i,j,p;
  for(i=0;i<k-1;i++)    
    clean_and_append(&head,&tail,A,i,k);    
  for(p=0;i<n;i++)
    {
      clean_and_append(&head,&tail,A,i,k);
      pop_front(&head,&tail,&j);    
      cout<<p++<<"th window max= "<< A[j]<<endl;
    }
}

/*************************************/
int main()
{
  char s[]="vik";
  int A[]={1,2,3,1,4,5,2,3,6},k=3,i,j,size;
  size=sizeof(A)/sizeof(*A);
  
  // for(i=0;i<size;i++) cout <<A[i] <<", ";
  // cout<<endl;
  
  Max_in_each_window_of_size_k(A,size,k);
  //cout <<index_of_flipping_0_giving_longest_chains_of_1s(A,size)<<endl;
  // cout << find_pivot(A,size);
  //combination(s,3);
  //permutation(s,0);
  // Arrange_pos_neg_alternately(A,size);
  // for(i=0;i<size;i++) cout <<A[i] <<", ";
  //cout<<endl;



  return 0;
}
