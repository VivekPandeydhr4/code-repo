#include<stdio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
/*******************************************************/
typedef struct node
{
  unsigned long long data;
  struct node * next;
}NODE;

/*******************************************************/
void print_list(NODE *head)
{
  NODE *temp=NULL;
  printf("\n\tList: ");
  for(temp=head;temp;temp=temp->next)
    printf("%lld ",temp->data);
  printf("\n");

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
NODE* create_list(int *A, int n)
{
  int i;
  NODE *head=NULL;
  for(i=0;i<n;i++)
    {
      head=append(head,A[i]);
    }
  return head;
}
/*****************************************************/
NODE* fun1(NODE *h1, NODE *h2 , int *carry)
{
  NODE *h=NULL,*newnode;

  if(!h1) {*carry=0; return NULL;}  
  h=fun1(h1->next,h2->next,carry);
  newnode=(NODE*)malloc(sizeof(NODE));
  newnode->next=h;newnode->data=(h1->data+h2->data+*carry)%10;
  *carry=(h1->data+h2->data+*carry)/10;
  return newnode;
}
NODE* sum_of_two_equal_length_no(NODE *h1, NODE *h2)
{
  int carry=0;
  NODE *h,*newnode;
  h=fun1(h1,h2,&carry);
  if(carry)
    {
      newnode=(NODE*)malloc(sizeof(NODE));
      newnode->data=carry;newnode->next=h;
      return newnode;
    }
  else return h;
}
void skipM_deleteN(NODE *head, int m , int n)
{
  int k;
  NODE *t,*temp;
  if(head)
    {
      for(temp=head,k=1;temp && k<m;temp=temp->next,k++);
      if(temp)
	{
	  k=0;
	  while(k<n){
	    t=temp->next;
	    if(t){temp->next=t->next;free(t);}
	    else break;
	    k++;
	  }	
	  if(temp->next) skipM_deleteN(temp->next,m,n);
	}
    }
}

int detect_loop(NODE *head)
{
  NODE *back,*current,*ahead;

  if(head)
    {
      if(head->next)
	{
	  back=NULL;current=head;ahead=head->next;
	  while(current)
	    {
	      current->next=back;
	      back=current;
	      current=ahead;
	      if(ahead)ahead=ahead->next;
	    }
	  if(back==head) return 1;
	  else return 0;
	}
      else return 0;
    }
  else return 0;

}

/*NODE* sum_of_three_integers(NODE *h1, NODE *h2, NODE *h3)
{//incomplete
  int l1,l2,l3,l,x;
  NODE *p1,*q1,*q2,*temp;
  
  for(temp=h1,l1=0;temp;l1++) temp=temp->next;
  for(temp=h2,l2=0;temp;l2++) temp=temp->next;
  for(temp=h3,l3=0;temp;l3++) temp=temp->next;

  if(l1<l2) {temp=h1;h1=h2;h2=temp; x=l1;l1=l2;l2=x;}
  if(l2<l3) {temp=h2;h2=h3;h3=temp; x=l2;l2=l3;l3=x;}
  if(l1<l2) {temp=h1;h1=h2;h2=temp; x=l1;l1=l2;l2=x;}

  for(temp=h1,l=1;temp;l++)
    {
      if(l==l1-l2) p1=temp;
      if(l==l1-l3) {q1=temp;break;}
      temp=temp->next;
    }
  for(temp=h2,l=1;l<l2-l3;l++) temp=temp->next;
  q2=temp;

  carry=0;
  third=Add_3_lists(q1->next,q2->next,h3,&carry,3,&tail);
  r1=q1->next;r2=q2->next;
  q1->next=q2->next=NULL;
  second=Add_3_lists(p1->next,h2,NULL,&carry,2,&tail);
  tail->next=third;
  q1->next=r1;q2->next=r2;
  r3=p1->next;p1->next=NULL;
  first=Add_3_lists(h1,NULL,NULL,&carry,1,&tail);
  p1->next=r3;
  tail->next=second;
  p1->next=r3;
  while(carry) 
    {
      newnode=(NODE*)malloc(sizeof(NODE));
      newnode->data=carry%10;
      carry=carry/10;
      newnode->next==first;
      first=newnode;
    }
  return first;
}*/


NODE* maximum_sum_common_list(NODE *h1, NODE *h2)
{
  NODE *temp1,*temp2,*ret;
  int sum1,sum2;
  if(!h1) return h2;
  if(!h2) return h1;
  
  temp1=h1;temp2=h2;sum1=sum2=0;
  while(temp1 && temp2)
    {
      if(temp1->data < temp2->data)
	{
	  sum1+=temp1->data;
	  temp1=temp1->next;
	}
      else if(temp1->data >temp2->data)
	{
	  sum2+=temp2->data;
	  temp2=temp2->next;
	}
      else break;
    }
  if(temp1 && temp2)
    {
      ret=maximum_sum_common_list(temp1->next,temp2->next);
      if(sum1>=sum2) {temp1->next=ret; return h1;}
      else {temp2->next=ret;return h2;}      
    }
  if(temp1)
    {
      while(temp1) {sum1+=temp1->data;temp1=temp1->next;}
      if(sum1>=sum2) return h1;
      else return h2;
    }
  if(temp2)
    {
      while(temp2) {sum2+=temp2->data;temp2=temp2->next;}
      if(sum2>=sum1) return h2;
      else return h1;
    }  
}

NODE* reverse_alternate_and_append(NODE *head)
{
  NODE *head2=NULL,*temp=NULL,*prev=NULL,*t=NULL;

  for(temp=head;temp && temp->next;prev=temp,temp=temp->next)
    {
      t=temp->next->next;
      temp->next->next=head2;
      head2=temp->next;
      temp->next=t;     
    }
  if(temp) temp->next=head2;
  else if(prev) prev->next=head2;
  return head; 
}

NODE* Sort_0s_1s_2s(NODE *head)
{
  NODE *H0,*T0,*H1,*T1,*H2,*T2,*H,*T,*temp,*t;
  H0=T0=H1=T1=H2=T2=NULL;
  for(temp=head;temp;)
    {
      t=temp->next;temp->next=NULL;
      switch(temp->data)
	{
	case 0:
	  if(!H0) H0=T0=temp;
	  else {T0->next=temp;T0=temp;}
	  break;
	case 1:
	  if(!H1) H1=T1=temp;
	  else {T1->next=temp;T1=temp;}
	  break;

	case 2:
	  if(!H2) H2=T2=temp;
	  else {T2->next=temp;T2=temp;}
	  break;
	}
      temp=t;
    }
  H=T=NULL;
  if(H0) {H=H0;T=T0;}
  if(H1)
    {
      if(!H) {H=H1;T=T1;}
      else {T->next=H1;T=T1;}
    }
  
  if(H2)
    {
      if(!H) {H=H2;T=T2;}
      else {T->next=H2;T=T2;}
    }
  return H;
}

NODE* Quick_Sort(NODE *head,NODE **tail)
{
  NODE *temp,*t,*tail1,*tail2,*H1,*T1,*H2,*T2;
  *tail=tail1=tail2=H1=T1=H2=T2=NULL;
  if(head)
    {
      for(temp=head->next;temp;)
	{
	  t=temp->next;temp->next=NULL;
	  if(temp->data<head->data)
	    {
	      if(!H1) H1=T1=temp;
	      else {T1->next=temp;T1=temp;}
	    }
	  else 
	    {
	      if(!H2) H2=T2=temp;
	      else {T2->next=temp;T2=temp;}
	    }
	  temp=t;
	}
      head->next=NULL;

      (*tail)=head;

      if(H1) {H1=Quick_Sort(H1,&tail1);tail1->next=head;head=H1;}

      if(H2) {H2=Quick_Sort(H2,&tail2);(*tail)->next=H2;*tail=tail2;}     
    }
  return head;
  
}

NODE* remove_nodes_having_greater_along_right_side(NODE *head)
{
  NODE *h=NULL;
  if(head)
    {
      if(head->next)
	{
	  h=remove_nodes_having_greater_along_right_side(head->next);
	  if(head->data >= h->data) {head->next=h; return head;}
	  else return h;
	}
      return head;
    }
  else return NULL;
}

NODE* reverse(NODE *head)
{
  NODE *r=NULL;
  if(head)
    {
      if(head->next)
	{
	  r=reverse(head->next);
	  head->next->next=head;
	  head->next=NULL;
	  return r;
	}
      else return head;
    }
  else return NULL;
}

NODE* Reverse_alternate_k_nodes(NODE *head, int k)
{
  NODE *t,*temp,*r;
  int c;
  if(head)
    {
      for(temp=head,c=1;temp && c<k;c++,temp=temp->next);

      t=NULL;
      if(temp) {t=temp->next;temp->next=NULL;}

      r=reverse(head);
      for(temp=t,c=1;temp && c<k;c++,temp=temp->next);
      head->next=t;
      
      if(temp) temp->next=Reverse_alternate_k_nodes(temp->next,k);
      return r;
    }
  else return NULL;
}
NODE* Reverse_every_k_nodes(NODE *head, int k)
{
  NODE *temp=NULL,*t=NULL,*r=NULL;
  int c=0;
  if(head)
    {
      for(temp=head, c=1;temp && c<k ; c++, temp=temp->next);
      t=NULL;
      if(temp) {t=temp->next;temp->next=NULL;}
      r=reverse(head);
      t=Reverse_every_k_nodes(t,k);
      head->next=t;
      return r;
    }
  else return NULL;
}

NODE* sorted_merge_of_two_Sorted_lists(NODE *h1, NODE *h2)
{
  if(!h1) return h2;
  if(!h2) return h1;
  if(h1->data <= h2->data) {h1->next=sorted_merge_of_two_Sorted_lists(h1->next,h2); return h1;}
  else {h2->next=sorted_merge_of_two_Sorted_lists(h1,h2->next); return h2;}
}
NODE* Remove_duplicates(NODE *head)
{
  NODE *r=NULL;
  if(head)
    {
      if(head->next)
	{
	  r=Remove_duplicates(head->next);
	  if(r->data==head->data) {free(head); return r;}
	  else {head->next=r; return head;}
	}
      else return head;
    }
  else return NULL;
}
NODE* Alternate_merge(NODE *h1, NODE *h2)
{
  if(!h1) return h2;
  if(!h2) return h1;
  
  h2->next=Alternate_merge(h1->next,h2->next);
  h1->next=h2;
  return h1;
}
NODE* Alternate_split(NODE *head)
{
  NODE *second=NULL,*t=NULL;
  if(head)
    {
      if(head->next)
	{
	  second=head->next;
	  t=Alternate_split(head->next->next);
	  head->next=head->next->next;
	  second->next=t;
	  return second;
	}
      else return NULL;
    }
  else return NULL;
}

NODE* Add_carry(NODE *head, NODE *t, int *carry)
{
  NODE *newnode=NULL;
  newnode=(NODE*)malloc(sizeof(NODE));
  if(head==t) newnode->next=NULL;
  else newnode->next=Add_carry(head->next,t,carry);
  newnode->data=(head->data+*carry)%10;
  *carry=(head->data+*carry)/10;
}
NODE* Sum_Equal_ListNumbers(NODE *head1, NODE *head2,int *carry)
{
  int s;
  NODE *newnode=NULL;
  if(!head1) return NULL;
  newnode=(NODE*)malloc(sizeof(NODE));  
  newnode->next=Sum_Equal_ListNumbers(head1->next,head2->next,carry);    
  s=head1->data+head2->data+*carry;
  newnode->data=s%10;
  *carry=s/10;  
  return newnode;
}


NODE* Sum_ListNumbers(NODE *head1, NODE *head2)
{
  int x,l1,l2,carry,l; NODE *First,*Second,*temp,*t,*newnode;
  //if(!head1) return copy(head2);
  //if(!head2) return copy(head1);
  
  for(t=head1,l1=0;t;t=t->next,l1++);
  for(t=head2,l2=0;t;t=t->next,l2++);
  carry=0;
  
  if(l1==l2) Second=Sum_Equal_ListNumbers(head1,head2,&carry);
  else
    {
      if(l1<l2){t=head1;head1=head2;head2=t;x=l1;l1=l2;l2=x;}
      for(l=1,t=head1;l<l1-l2;t=t->next,l++);
      Second=Sum_Equal_ListNumbers(t->next,head2,&carry);
      First=Add_carry(head1,t,&carry);
      for(temp=First;temp->next;temp=temp->next);
      temp->next=Second;
      Second=First;
    } 
  if(carry){
    newnode=(NODE*)malloc(sizeof(NODE));
    newnode->data=carry; newnode->next=Second;
    Second=newnode;
  }
  return Second;
}
/*****************************************************/
int main()
{
  NODE *h,*g,*result,*temp=NULL;
  int size_of_A,size_of_B,size,size_A,size_B;
//int A[]={0,1,2,1};//{2,1,1,0,1,2,0,0,0,2,2,2,1,1,0,1,2,1,2,1};
int A[]={1,3,5,7,9},B[]={2,4,6,8};
//int A[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21},B[]={9,9,9,9,5,6,7,8,9};
  size_A=sizeof(A)/sizeof(*A);
  size_B=sizeof(B)/sizeof(*B);

 
  
  h=create_list(A,size_A);
  print_list(h);

  
  g=create_list(B,size_B);
  print_list(g);

  print_list(Sum_ListNumbers(h,g));

  //print_list(h);
  // print_list(result);
  // result=Alternate_split(h);
//h=Remove_duplicates(h);
  //h=Reverse_every_k_nodes(h,10);
  //h=Reverse_alternate_k_nodes(h,11);
  // h=Quick_Sort(h,&temp);
  // print_list(h);
  //print_list(Sort_0s_1s_2s(h));

  // print_list(reverse_alternate_and_append(h));
  // print_list(reverse_alternate_and_append(g));

  //print_list(maximum_sum_common_list(h,g));
  // for(temp=h;temp->next;temp=temp->next);
  // temp->next=h->next;//->next->next->next->next->next->next->next->next;
  // cout<<detect_loop(h)<<endl;
  // skipM_deleteN(h,4,3);
  // print_list(h);
  // h=create_list(B,size_of_B);
  // g=create_list(B,size_of_B);
  // print_list(h);
  // print_list(g);
  // result=sum_of_two_equal_length_no(h,g);
  // print_list(result);
  return 0;
}
