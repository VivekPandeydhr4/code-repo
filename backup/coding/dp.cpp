#include <iostream>
#include <cstdio>

using namespace std;

/***************************************************/
int max_sum_with_no_consecutive_elements(int *A,int n)
{
  int sum=0,back_sum=0,i,t;

  for(i=0;i<n;i++)
    {
      t=back_sum+A[i];
      back_sum=sum;
      if(t>sum) sum=t;
    }
  return sum;
}

void print_end_of_the_row(int n,int square, int row)
{
  int i,base;
  if(row==1){
    base=square*square-(square+1)/2;
    for(i=base;i>base-(square)/2;i--) cout<<i<<"  ";
  }
  else if(row==square){
    base = square*square-3*square+3+(square+1)/2;
    for(i=base;i<base+(square)/2;i++) cout<<i<<"  ";
  }
  else if(row>1 && row<square)
    {
      cout<<square*square-square+2-row<<"  ";
    }
  if(square==n) cout <<endl;
}

void print_start_of_the_row(int n, int square, int row)
{
  int i,base;
  if(row==1){
    base=square*square;
    for(i=base;i>base-(square+1)/2;i--) cout<<i<<"  ";
  }
  else if(row==square){
    base = square*square-3*square+3;
    for(i=base;i<base+(square+1)/2;i++) cout<<i<<"  ";
  }
  else if(row>1 && row<square)
    {
      cout<<square*square-4*square+3+row<<"  ";
    }

}

void print_row(int n, int square, int row)
{
  if(square>0 && row>0)
    {
      print_start_of_the_row(n, square,row);
      print_row(n, square-2,row-1);
      print_end_of_the_row(n, square,row);

    }
}

void print_matrix_whose_data_are_filled_spirally_as_1_2_(int n)
{
  int i;
  for(i=1;i<=n;i++)
    {
      print_row(n,n,i);
    }
}



/***************************************************/
int main()
{
  int x,n, A[]={5,5,10,100,10,5};
  n=sizeof(A)/sizeof(A[0]);
  //print_end_of_the_row(6,6);
  //print_row(4,2);
  //print_end_of_the_row(5,3);
  //print_row(5,1);
  cout<<"Enter Order of the matrix: ";
  cin>>x;
  print_matrix_whose_data_are_filled_spirally_as_1_2_(x);
  //cout<< max_sum_with_no_consecutive_elements(A,n)<<endl;
    
  return 0;
}
