#include<stdio.h>
#include<stdlib.h>

/*** STRUCTURE DEFINITION ***/
typedef struct NODE
{
  int data;
  struct NODE *next;
}node;

/*** FUNCTION PROTOTYPE ***/
node* create_node(int num);
node* append_node(node* head, int num);
node* prepand_node(node* head, int num);
node* create_list_s();
node* alternate_rev(node* head);
void recursiveReverse(node** head_ref);
node* reverse(node* head);
void print_list(node* head);
void print_recursive(node* head);

int main()
{
  node* head = NULL;

  head = create_list_s();
  print_recursive(head);
  head=reverse(head);
  printf("\n");
  print_list(head);
  //  head = alternate_rev(head);
  //  recursiveReverse(&head);
  // print_list(head);

  printf("\n");
  return 0;
}

node* create_node(int num)
{
  node *newnode;
  newnode = (node*)malloc(sizeof(node));
  newnode->data = num;
  newnode->next = NULL;
  return newnode;
}

node* append_node(node* head, int num)  
{
  node* newnode = create_node(num);
  node* temp;
  if(head==NULL) return newnode;
  else{
    for(temp=head;temp->next!=NULL;temp=temp->next);
    temp->next = newnode;
    return head;
  }
}

node* prepand_node(node* head, int num)
{
  node* newnode = create_node(num);
  
  newnode->next = head;
  return newnode;
}
node* create_list_s()
{
  node* head = NULL;
  head = append_node(head, 1);
  head = append_node(head, 2);
  head = append_node(head, 3);
  head = append_node(head, 4);
  head = append_node(head, 5);
  head = append_node(head, 6);
  head = append_node(head, 7);
  head = append_node(head, 8);
  head = append_node(head, 9);
  head = append_node(head, 10);
  /*  head = prepand_node(head, 1);
  head = prepand_node(head, 2);
  head = prepand_node(head, 3);
  head = prepand_node(head, 4);
  head = prepand_node(head, 5);
  head = prepand_node(head, 6);
  head = prepand_node(head, 7);*/

  return head;
}

node* alternate_rev(node* head)
{
  node* temp;
  node* alt;

  temp=head;
  alt= temp->next;
  head=alt;

  temp->next=alt->next;
  alt->next = temp;
  for(;temp!=NULL&&alt!=NULL;)
    {
      alt=temp->next;
      temp->next=alt->next;
      alt->next = alt->next->next;
      temp->next->next = alt;
      if(temp==NULL || temp->next==NULL) break;
      temp=alt;
      alt=temp->next;
    }

  return head;
}
void recursiveReverse(node** head_ref)
{
     node* first;
     node* rest;

    /* empty list */
    if (*head_ref == NULL)
       return;  

    /* suppose first = {1, 2, 3}, rest = {2, 3} */
    first = *head_ref;
    rest  = first->next;

    /* List has only one node */
    if (rest == NULL)
       return;  

    /* put the first element on the end of the list */
    recursiveReverse(&rest);
    first->next->next  = first; 

    /* tricky step -- see the diagram */
    first->next  = NULL;         

    /* fix the head pointer */
    *head_ref = rest;
}

node* reverse(node* head)
{
/*  node* temp;
  if(head->next==NULL) 
    {
         temp = head;
	 return temp;
    }
  else
    {
      reverse(head->next);
      head->next->next = head;
      // head->next = NULL;
      return temp;
      }
  
	 //     return temp;
	 */
	 
	   node *temp=NULL;
    if(head)
    {
	if(head->next==NULL)
	    return head;
	else
	{
	    temp=reverse(head->next);
	    head->next->next=head;
	    head->next=NULL;
	    return temp;
	}
    }

}

void print_list(node* head)
{
  node* temp;
  for(temp=head;temp!=NULL;temp=temp->next)
    printf("%d ",temp->data);

  printf("\n");
}
void print_recursive(node* head)
{

  if(head==NULL)
    return ;
  else
    {
        printf("%d ",head->data);
      print_recursive(head->next);
      // printf("%d ",head->data);
    }
}

