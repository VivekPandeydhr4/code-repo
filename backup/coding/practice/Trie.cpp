#include <stdio.h>
#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct node
{
  int flag;
  struct node * A[26];
}NODE;
/************************************/

NODE* Insert2(NODE *T, const char *s)
{
  int i;
  if(T==NULL)
    {
      T=(NODE*)malloc(sizeof(NODE));
      T->flag=0;
      for(i=0;i<26;i++) T->A[i]=NULL;		  	
    }
  if(!*s)  T->flag=1;
  else   T->A[*s-'a']=Insert2(T->A[*s-'a'],s+1);
            
  return T;
}

int Search2(NODE *T, const char *s) 
{
  if(!T) return 0;
  if(!*s) return T->flag;
  return Search2(T->A[*s-'a'],s+1);
}

int main()
{
  int i;
  NODE *T=NULL;
  char words[][20]={"ramlakhan","sharda", "shyam", "nirmala", "vikas", "kanchan","vivek","vipin","brajesh", "ayush"};
  char toSearch[][20]={"ramlakhan","sharda", "shyam", "nirmala", "vikas", "kanchan","vivek","vipin","brajesh", "ayush"};
  
  for(i=0;i<10;i++)
    T=Insert2(T,words[i]);
  for(i=0;i<10;i++)
    cout<< Search2(T,words[i])<<",";
  cout<< Search2(T,"shambhu")<<"..";
  cout<< endl;
}
