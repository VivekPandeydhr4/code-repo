#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;
/***********************************************************/
typedef struct node 
{
  int data;
  struct node *next;
}NODE;

typedef struct Dnode 
{
  int data;
  struct node *next,*prev;
}DNODE;

/***********************************************************/
void print_list(NODE *head)
{
  NODE *temp=NULL;
  printf("\n\tList: ");
  for(temp=head;temp;temp=temp->next)
    printf("%d ",temp->data);
  printf("\n");

}
NODE* build_list()
{
  return (NODE*)NULL;
}

NODE* append(NODE *head,int x)
{
  NODE *temp=NULL;
  NODE* newnode=(NODE*)malloc(sizeof(NODE));
  newnode->data=x;
  newnode->next=NULL;
  if(!head) return newnode;
  for(temp=head;temp->next;temp=temp->next);
  temp->next=newnode;
  return head;
}
 
NODE* prepend(NODE *head, int x)
{
  NODE *newnode=(NODE*)malloc(sizeof(NODE));
  newnode->data=x;
  newnode->next=head;
  return newnode;
}
/*DNODE* reverse_DLL(DNODE *head)
{//DLL: with return value
  DNODE* toRet;
  if(head)
    {
      if(head->next)
	{
	  head->next->prev=NULL;
	  toRet=reverse_DLL(head->next);
	  head->next->next=head;
	  head->prev=head->next;
	  head->next=NULL;
	  return toRet;
	}
      else return head;
    }
  else return NULL;
  }*/

void Reverse(NODE** head)
{//SLL:  without return value
  NODE* temp;
  if(*head)
    {
      if((*head)->next)
	{
	  temp=(*head)->next;
	  Reverse(&((*head)->next));
	  temp->next=*head;
	  temp=(*head)->next;
	  (*head)->next=NULL;
	  *head=temp;
	}      
    }
}

NODE *reverse(NODE *head)
{// SLL: with return value
  NODE *toReturn;
  if(head)
    {
      if(head->next)
	{
	  toReturn=reverse(head->next);
	  head->next->next=head;
	  head->next=NULL;
	  return toReturn;
	}
      else return head;
    }
  else return NULL;
}
int isPal(int n, int *r)
{//helping function for isPalindrome
  int f;
  if(n)
    {
      f=isPal(n/10,r);
      if(f && (n%10==(*r)%10))
	{  
	  (*r)=(*r)/10;
	  return 1;
	}
      else return 0;
    }
  else return 1;
}
void isPalindrome(int n)
{
  int r;
  r=n;
  if(isPal(n,&r)) printf("Palindrome\n");
  else printf("Not a Palindrome\n");
}
int multiplication_using_minimum_addition(int a, int b)
{// for all integers inputs (-ve as well)
  int t,x,f;
  if(!a||!b) return 0;
  f=a*b<0?-1:1;
  if(a<0) a*=(-1);
  if(b<0) b*=(-1);
  if(a<b) {t=a;a=b;b=t;}  
  x=multiplication_using_minimum_addition(a,b/2);
  if(b%2) return (x+x+a)*f;
  else return (x+x)*f;
}
void pair_for_a_Sum(int *A, int n, int sum)
{
  int i,j;
  if(n)
    {
      sort(A,A+n);
      for(i=0,j=n-1;i<j;)
	{
	  if(A[i]+A[j]==sum) {printf("%d=%d+%d\n",sum,A[i],A[j]);break;}
	  else if(A[i]+A[j]<sum) i++;
	  else j--;
	}
      if(i==j)  printf("No such pair for %d\n",sum);
    }
  else printf("Empty array\n");
}

void smallest_111s_divisible_by_number_with_3_at_unit(int n)
{
  int x,sum,r;
  x=n; sum=0;
  while(x) {sum=sum*10+1;x/=10;}
  cout<<sum;
  r=sum;  
  while(r)
    {
      cout <<1;
      r=(r*10+1)%n;
    }
}
/*
int isIdentical(NODE *root1, NODE *root2)
{//Working code for identicality of two Binary tree
  if(!root1 && !root2) return 1;
  if(root1 && root2)
    {
      if(root1->data==root2->data && isIdentical(root1->left,root2->left) && isIdentical(root1->right, root2->right)) return 1;
      else return 0;
    }
  else return 0;
}

int check_BST(NODE *root, int *min, int *max)
{//Working code to check whether Binary tree is BST or not.
  int lmin,lmax,rmin,rmax,x,y;
  if(!root) return 1;  
  *min=*max=root->data;
  if(root->left)
    {
      x=check_BST(root->left,&lmin, &lmax);
      if(x && lmax<*min){*min=lmin; return 1;}
      else return 0;
    }
  if(root->right)
    {
      y=check_BST(root->right,&rmin,&rmax);
      if(y && *max<=rmin) {*max=rmax; return 1;}
      else return 0;
    }
  return 1;
}

*/
NODE* sorted_insert(NODE *head, int x)
{
  NODE *newnode,*temp;
  newnode=(NODE*)malloc(sizeof(NODE));
  newnode->data=x;
  newnode->next=NULL;
  if(!head) return newnode;
  if(head->data>=x) {newnode->next=head; return newnode;}
  for(temp=head;temp->next;temp=temp->next) if(temp->next->data>=x) break;
  newnode->next=temp->next;
  temp->next=newnode;
  return head;
}


int A_minus_B_duplicate_removals(int *A, int m, int *B, int n, int *C)
{
  int i,j,k;
  if(m>0)
    {
      for(i=j=k=0;i<m;)
	{
	  if(i && A[i-1]==A[i]) {i++;continue;}
	  if(j>=n){C[k++]=A[i++];}
	  else if(B[j]<A[i]) j++;
	  else if(A[i]==B[j]) {i++;j++;}
	  else C[k++]=A[i++];
	}
      return k;
    }
  else return 0;
}

int No_of_flip_bits(unsigned int a , unsigned int b)
{
  int x,count=0;
  x=a^b;
  while(x)
    {
      if(x & 1) count++;
      x=x>>1;
    }
  return count;
}
#define ROW 5
#define COL 6

int b_search(int *A, int s, int e)
{
  int mid;
  if(s<=e)
    {
      mid=s+(e-s)/2;
      if(A[mid] && !A[mid+1]) return mid;
      else if(!A[mid]) return b_search(A,s,mid-1);
      else return b_search(A,mid+1,e);
    }
}
int binary_search(int *A, int s, int e)
{
  if(A[e]){ return e;}
  return b_search(A,s,e-1);
}
int row_of_maximum_1s(int M[][COL])
{
  int i,k,toRet,j;
  k=0;toRet=-1;
  for(i=0;i<ROW;i++)
    {
      if(M[i][k]){
	j=binary_search(M[i],k,COL-1);
	k=j+1;toRet=i;
	if(k==COL) break;
      }
    }
  //cout <<k<<":";
  return toRet;
}

/***********************************************************/
int main()
{
  int Asize,Bsize;
  int i,j,a,b,A[]={1,3,3,5,6,7,9,51},B[]={2,3,6,7,12,13,24,34,51},C[100];
  NODE *second,*head=build_list(),*head2=build_list();  

  int M[ROW][COL]={{1,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
  for(i=0;i<ROW;i++)
    {
      for(j=0;j<COL;j++)
	cout <<M[i][j]<<" ";
      cout <<endl;
    }
  cout << row_of_maximum_1s(M)<<endl;
  // while(1){cin>>a>>b;
  //   cout << No_of_flip_bits(a,b)<<endl;}
  /*Asize=sizeof(A)/sizeof(A[0]);
  Bsize=sizeof(B)/sizeof(B[0]);
  a=A_minus_B_duplicate_removals(A,Asize,B,Bsize,C);

  for(i=0;i<Asize;i++) cout <<A[i]<<" ";
  cout<<endl;


  for(i=0;i<Bsize;i++) cout <<B[i]<<" ";
  cout<<endl;

  for(i=0;i<a;i++) cout <<C[i]<<" ";
  cout<<endl;*/
  /*smallest_111s_divisible_by_number_with_3_at_unit(3);
  printf(":3\n");
  smallest_111s_divisible_by_number_with_3_at_unit(13);
  printf(":13\n");
  smallest_111s_divisible_by_number_with_3_at_unit(23);
  printf(":23\n");*/
  /*  for(i=0;i<10;i++) printf("%d ",A[i]);
  printf("\n");
  pair_for_a_Sum(A,10,31);*/
  
  /*while(1){
  cin >>a>>b;
  cout <<multiplication_using_minimum_addition(a,b)<<endl;
  }*/

  /*  do{
    scanf("%d",&a);
    if(a<=0) break;
    isPalindrome(a);
    }while(1);*/

  /*  printf("Enter list data:");
  while(1)
    {
      scanf("%d",&a);
      if(a==-1) break;
      head=append(head,a);
    }
   print_list(head);
   printf("\n");
   head=sorted_insert(head,5);
   //head=reverse(head);
   //Reverse(&head);
   print_list(head);
   printf("\n");
  */
  return 0;
}
