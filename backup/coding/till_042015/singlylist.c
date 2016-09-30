#include<stdio.h>
#include<stdlib.h>

/*******************************************************/
typedef struct node
{
  unsigned long long data;
  struct node * next;
}NODE;

/*******************************************************/
NODE* append(NODE *head,int x);
NODE* prepend(NODE *head, int x);
NODE* build_list();
void print_circular_list(NODE *head);
void reverse_circular_list(NODE *head);
void reverse_circular_list_recly(NODE *head);
void make_circular_list(NODE *head);
void print_list(NODE *head);
NODE* reverse_list(NODE *head);
NODE* reverse_k_elem(NODE *head, int k);
NODE* reverse_k_elem_recly(NODE *head, int k);
NODE* split_at_mid(NODE *head);
NODE* swap_pairs_itly(NODE *head);
NODE* swap_pairs_recly(NODE *head) ;
NODE* sorted_merge_itly(NODE *h1, NODE *h2);
NODE* sorted_merge_recly(NODE *h1, NODE *h2);
NODE* suffle_merge_itly(NODE *h1,NODE *h2);
NODE* merge_sort(NODE *head);
void Merge(NODE *first, NODE **second);
int palindrome(NODE *h);
int pal(NODE **h1, NODE *h2);
void Merge_itly(NODE *f, NODE **s);
void Remove_duplicate(NODE *root);
NODE* Kth_lastNode(NODE *head, int k);
NODE* Reverse_k_Elem(NODE *head, int k);
NODE* Reverse_K_elem(NODE *head, int k);
NODE* sortList_0_1(NODE *head);
int check_palindrome(NODE *head);
int check_pal(NODE *head, NODE **toMatch);
NODE* Alternate_Merge(NODE *h1, NODE *h2);
NODE* reverse(NODE *head);
NODE* rev_k_nodes(NODE *head,int k);
NODE *Rev_k_nodes(NODE *head, int k);
NODE* sorted_merging(NODE *h1, NODE *h2);
NODE* k_group_reversal(NODE *root, int k);
NODE* rotate_list_by_k(NODE *head, int k);
int isPal(NODE** H,NODE *T);
/*******************************************************/
int isPal(NODE **H, NODE *T)
{
  if(T)
    {
      if(isPal(H,T->next)&& T->data==(*H)->data) {(*H)=(*H)->next; return 1;}
      else return 0;
    }
  else return 1;
}
int Palindrome(NODE *head)
{
  NODE *H,*T;
  if(!head) return 1;
  H=T=head;
  return isPal(&H,T);
}

int main()
{
  int a;
  NODE *second,*head=build_list(),*head2=build_list();

  printf("Enter list data:");
  while(1)
    {
      scanf("%d",&a);
      if(a==-1) break;
      head=append(head,a);
    }
   print_list(head);
   printf("\n");

   printf("%d\n", Palindrome(head));
   //head=rotate_list_by_k(head,20);
  /* while(1) */
  /*   { */
  /*     scanf("%d",&a); */
  /*     if(a==-1) break; */
  /*     head2=append(head2,a); */
  /*   } */
  //printf("%d\n",check_palindrome(head));
  //head=Reverse_K_elem(head,3);
   print_list(head);
   printf("\n");
   //print_list(head2);
   /* head=Alternate_Merge(head,head2); */
   /* printf("\n"); */
   /* head=sorted_merging(head,head2); */
   /* head=k_group_reversal(head,3); */
   /* print_list(head); */
   /* printf("\n"); */
   //head=sortList_0_1(head);
  //second=Kth_lastNode(head,1); 
  //Remove_duplicate(head);
  //printf("%d\n",second->data);
  //print_list(head);
  /* printf("  Enter data list2: "); */
  /* while(1) */
  /*   { */
  /*     scanf("%d",&a); */
  /*     if(a==-1) break; */
  /*     head1=append(head1,a); */
  /*   } */
  /* print_list(head); */
  /* print_list(head1); */
  /* Merge_itly(head,&head1); */
  /* print_list(head); */
  /* print_list(head1); */

  return 0;
}

NODE* rotate_list_by_k(NODE *head, int k)
{
  NODE *t,*t2,*h;
  int i;
  if(!head||!k) return  NULL;
  t2=NULL;
  for(t=head, i=1;t->next;t=t->next,i++)
    {
      if(i==k) t2=t;
    }
  if(t2){h=t2->next;t2->next=NULL;t->next=head;return h;}
  else return head;
}

NODE* k_group_reversal(NODE *head, int k)
{
  int i;
  NODE *temp,*last,*current,*t,*prev;
  last=NULL;
  current=head;
  while(current)
    {
      for(i=1,temp=current;temp && i<k ;i++)
	{
	  prev=temp; temp=temp->next;
	}
      if(!temp) temp=prev;
      prev=temp->next;
      temp->next=last;
      last=current;
      current=prev;
    }
  return last;
}


NODE* sorted_merging(NODE *h1, NODE *h2)
{
  NODE *toRet,*back,*t;
  if(!h1) return h2;
  if(!h2) return h1;
  toRet=back=NULL;
  while(h1 && h2)
    {
      if(h1->data <= h2->data) {t=h1;h1=h1->next;}
      else {t=h2;h2=h2->next;}
      if(!toRet) toRet=t;
      else back->next=t;
      back=t;
    }
  if(!h1) back->next=h2;
  else back->next=h1;
  return toRet;
}

NODE *Rev_k_nodes(NODE *head, int k)
{
  NODE *temp,*toRet,*h,*t,*back;
  int i;
  toRet=NULL;
  temp=head;
  while(temp)
    {
      h=temp;
      for(i=1;temp && i<k;i++) temp=temp->next;      
      if(temp)
	{
	  t=temp;
	  temp=temp->next;
	  t->next=NULL;
	}
      t=reverse(h);
      if(toRet)  back->next=t;
      else toRet=t;
      back=h;
    }
  return toRet;
}
NODE *rev_k_nodes(NODE* head, int k)
{
  int i=0;
  NODE *temp,*t,*l;
  if(head)
    {
      for(temp=head,i=1;temp && i<k;i++,temp=temp->next);
      t=NULL;
      if(temp)
	{
	  t=rev_k_nodes(temp->next,k);
	  temp->next=NULL;
	}
      l=reverse(head);
      head->next=t;
      return l;
    }
  return NULL;
}


NODE* reverse(NODE *head)
{
  NODE *l=NULL;
  if(head)
    {
      if(head->next)
	{
	  l=reverse(head->next);
	  head->next->next=head;
	  head->next=NULL;
	  return l;
	}      
    }
  return head;

}
NODE* Alternate_Merge(NODE *h1, NODE *h2)
{
  NODE *t,*h;
  h=h1;
  if(!h1) return h2;
  if(!h2) return h1;
  while(h1&&h2)
    {t=h1->next;
      h1->next=h2;
      h1=t;
      t=h2->next;
      if(h1) h2->next=h1;
      h2=t;
    }
  return h;
}


NODE* sortList_0_1(NODE *head)
{
  NODE *H,*T,*temp,*prev;
  H=T=NULL;
  if(head)
    {
      for(prev=NULL,temp=head;temp;)
	{
	  if(!temp->data)
	    {
	      if(!H)H=T=temp; else {T->next=temp;T=temp;}
	      if(!prev)
		{  head=head->next;temp->next=NULL;temp=head;}

	      else
		{
		  prev->next=temp->next;
		  temp->next=NULL;
		  temp=prev->next;
		}
	    }
	  else {prev=temp;temp=temp->next;}
	}
      
      if(T){T->next=head;return H;}
      else return head;
    }
  else return NULL;

}
int check_palindrome(NODE *head)
{
  NODE *toMatch=head;
  return check_pal(head, &toMatch);
}
int check_pal(NODE *head, NODE **toMatch)
{
  int a;
  if(head)
    {
      a=check_pal(head->next, toMatch);
      printf("%d ,%lld\n",a,head->data);
      if(a && (head->data==(*toMatch)->data))
	{
	  (*toMatch)=(*toMatch)->next;
	  return 1;
	}
      else return 0;
    }
  else return 1;

}
NODE* Reverse_k_Elem(NODE *head, int k)
{
  NODE *temp,*r,*R;
  int l;
  if(head)
    {
      for(l=1,temp=head; l<k && temp; l++, temp=temp->next);
      if(!temp)
	{
	  r=reverse_list(head);
	  return r;
	}
      else
	{
	  R=Reverse_k_Elem(temp->next,k);
	  temp->next=NULL;
	  r=reverse_list(head);
	  head->next=R;
	  return r;
	}
    }
  else return NULL;
}

NODE* Reverse_K_elem(NODE *head, int k)
{
  int l;
  NODE *temp,*temp1,*temp2,*r,*prev;
  
  prev=NULL;
  temp=head;
  if(k<=1) return head;
  while(temp)
    {
      for(temp1=temp,l=1;l<k&&temp1;l++,temp1=temp1->next);

      if(temp1)
	{
	  temp2=temp1->next;
	  temp1->next=NULL;
	  reverse_list(temp);
	  if(!prev) head=temp1;
	  else prev->next=temp1;
	  prev=temp;
	  temp=temp2;
	}
      else
	{
	  r=reverse_list(temp);
	  if(!prev) head=r;
	  else prev->next=r;
	  temp=NULL;
	}
    }
  return head;
}
NODE* Kth_lastNode(NODE *head, int k)
{
  NODE *t1,*t2;
  int count;
  if(k<1 || !head) return NULL;

  for(count=1,t1=head;t1;t1=t1->next)
    {
      if(count==k) break;
      count++;
    }
  if(count<k || !t1) return  NULL;
  
  t2=head;
  while(t1->next)
    {
      t1=t1->next;
      t2=t2->next;
    }
  return t2;
}


void Remove_duplicate(NODE *root)
{
  NODE *t1,*t2,*prev;
  if(root)
    {
      t1=root;
      while(t1 && t1->next)
	{
	  prev=t1;
	  t2=t1->next;
	  while(t2)
	    {
	      if(t2->data==t1->data)
		{
		  prev->next=t2->next;
		  free(t2);
		  t2=prev->next;
		}
	      else
		{
		  prev=t2;
		  t2=t2->next;
		}
	    }
	  t1=t1->next;
	}
    }
}
void Merge_itly(NODE *f, NODE **s)
{
  NODE *temp;
  while(f&&(*s))
    {
      temp=(*s)->next;
      (*s)->next=f->next;
      f->next=*s;
      f=(*s)->next;
      (*s)=temp;
    }
}

void Merge(NODE *f, NODE **s)
{
  NODE *temp;
  if(f)
    {
      if(*s)
	{
	  temp=*s;
	  (*s)=(*s)->next;
	  temp->next=f->next;
	  f->next=temp;
	  Merge(temp->next,s);
	}
    }

}

int palindrome(NODE *h)
{
  NODE *h1;
  h1=h;
  return pal(&h1,h);
}

int pal(NODE **h1, NODE *h2)
{
  if(h2)
    {
      if(pal(h1,h2->next)&&((*h1)->data==h2->data))
	{
	  (*h1)=(*h1)->next;
	  return 1;
	}
      else return 0;
    }
  else return 1;
}




NODE *merge_sort(NODE *head)
{//Working
  NODE *temp,*l,*r,*slow,*fast,*prev;
  //Braeking at the mid
  if(head && head->next)
    {
      slow=head;
      fast=head->next;
      while(fast && fast->next)
	{
	  slow=slow->next;
	  fast=fast->next->next;
	}

      l=head;r=slow->next;
      slow->next=NULL;
      //Recursion
      l=merge_sort(l);
      r=merge_sort(r);
      //Sorted merge
      prev=NULL;
      while(l && r)
	{
	  if(l->data > r->data) 
	    {//swap(l,r)
	      temp=l;  l=r;  r=temp;
	    }
	  temp=l->next;
	  l->next=r;
	  if(prev==NULL) head=l;
	  else prev->next=l;
	  prev=l;
	  l=temp;
	  prev->next=r;
	}
    }
  return head;
}

NODE* suffle_merge_itly(NODE *h1,NODE *h2)
{
  NODE *t1,*t2,*toRet,*prev,*temp;
  if(!h1) return h2;
  if(!h2) return h1;
  t1=h1;t2=h2;prev=NULL;
  while(t1&&t2)
    {
      temp=t1->next;
      t1->next=t2;
      if(!prev) toRet=t1;
      else prev->next=t1;
      prev=t2;
      t2=t2->next;
      t1=temp;
    }
  if(t1==NULL) prev->next=t2;
  else prev->next=t1;
  return toRet;

}
NODE* sorted_merge_itly(NODE *h1, NODE *h2)
{
  NODE *t1,*t2,*temp,*prev,*toRet;
  if(!h1) return h2;
  if(!h2) return h1;
  t1=h1;t2=h2;prev=NULL;
  while(t1&&t2)
    {
      if(t2->data < t1->data) 
	{temp=t1;t1=t2;t2=temp;}
      temp=t1->next;
      t1->next=t2;
      if(!prev) toRet=t1;
      else prev->next=t1;
      prev=t1;t1=temp;
    }
  if(t1==NULL) prev->next=t2;
  else prev->next=t1;
  return toRet;

}
NODE* sorted_merge_recly(NODE *h1, NODE *h2)
{
  NODE *t1;
  if(!h1) return h2;
  if(!h2) return h1;
  if(h1->data <= h2->data)
    {
      t1=sorted_merge_recly(h1->next,h2);
      h1->next=t1;
      return h1;
    }
  else
    {
      t1=sorted_merge_recly(h1,h2->next);
      h2->next=t1;
      return h2;
    }
}

NODE* swap_pairs_recly(NODE *head) 
{
  NODE *t,*ret;
  if(head)
    {
      if(head->next)
	{
	  ret=swap_pairs_recly(head->next->next);
	  head->next->next=head;
	  t=head->next;
	  head->next=ret;
	  return t;
	}
      
    }
  return head;
}


NODE* swap_pairs_itly(NODE *head)
{
  NODE *t1,*t2,*t3,*prev,*toReturn;
  prev=NULL;
  toReturn=head;
  if(head)
    {
      t1=head;
      if(head->next)
	{
	  t2=head->next;
	  while(t2)
	    {
	      t3=t2->next;
	      t2->next=t1;
	      t1->next=t3;
	      if(prev) prev->next=t2;
	      else toReturn=t2;
	      prev=t1;
	      t1=t3;
	      if(t1) t2=t1->next ;
	      else t2=NULL;
	    }
	}
    }
  return toReturn;
}



NODE *split_at_mid(NODE *head)
{
  NODE *first,*second;
  if(head)
    {
      first=head;
      second=first->next;
      while(second && second->next)
	{
	  first=first->next;
	  second=second->next->next;
	}
      second=first->next;
      first->next=NULL;
      return second;
    }
  else return NULL;

}
void remove_duplicates(NODE *head)
{


}


NODE *reverse_k_elem(NODE *head, int k)
{
  int i;
  NODE *current,*back,*prev,*t1,*t2,*toReturn;
  current=head;
  back=NULL;
  toReturn=head;
  while(current)
    {
      prev=NULL;
      t1=current;
      i=1;
      while(t1 && i<=k)
	{
	  t2=t1->next;
	  t1->next=prev;
	  prev=t1;
	  t1=t2;	  
	  i++;
	}
      if(back==NULL) toReturn=prev;
      else back->next=prev;
      back=current;
      current=t1;
    }
  return toReturn;

}


NODE *reverse_k_elem_recly(NODE *head, int k)
{
  int i;
 NODE *temp,*l,*prev;
 if(k>1)
   {
  if(head)
    {
      for(prev=NULL,temp=head,i=1; temp && i<=k; temp=temp->next,i++)
	prev=temp;
      prev->next=NULL;
      l= reverse_list(head);
      head->next=reverse_k_elem_recly(temp,k);
      return l;
    }
  else return head;
   }
 return head;
}

NODE* reverse_list(NODE *head)
{
  NODE *l;
  if(head)
    {
      if(head->next)
	{
	  l=reverse_list(head->next);
	  head->next->next=head;
	  head->next=NULL;
	  return l;
	}
      else return head;
    }
  else  return NULL;

}
void print_circular_list(NODE *head)
{
  NODE *temp=head;
  do
    {
      printf("%lld ",temp->data);
      temp=temp->next;      
    }while(temp!=head);
  printf("\n");

}
void reverse_circular_list(NODE *head)
{
  NODE *t1,*t2,*t3;
  if(head)
    {
      if(head->next!=head)
	{
	  if(head->next->next!=head)
	    {
	      t1=head;
	      t2=head->next;
	      t3=head->next->next;
	      do{
		t2->next=t1;
		t1=t2;
		t2=t3;
		t3=t3->next;
	      }while(t1!=head);		  
	    }

	}
    }
}
void reverse_circular_list_recly(NODE *head)
{
  NODE *temp;
  if(head)
    {
      if(head->next!=head)
	{
	  if(head->next->next!=head)
	    {
	      temp=head->next;
	      head->next=head->next->next;
	      reverse_circular_list_recly(head);
	      temp->next->next=temp;
	      temp->next=head;
	    }
	}
    }

}
void make_circular_list(NODE *head)
{
  NODE *temp;
  for(temp=head; temp->next ; temp=temp->next)
    ;
  temp->next=head;
}

void print_list(NODE *head)
{
  NODE *temp=NULL;
  printf("\n\tList: ");
  for(temp=head;temp;temp=temp->next)
    printf("%lld ",temp->data);
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
NODE* find_alternateSum(NODE* head)
{


}
