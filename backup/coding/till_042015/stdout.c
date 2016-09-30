#include <stdio.h>
#include <stdlib.h>
void Pascal_Tree(int n);
int main()
{
  Pascal_Tree(15);
  return 0;
}

void Pascal_Tree(int n)
{
  int *A=malloc((n+1)*sizeof(int));
  int *B=malloc((n+1)*sizeof(int));
  int *T1,*T2;
  int i,j,k,margin;
  for(i=0;i<=n;i++)
    {
      printf("\t\t\t\t\t");
      for(j=0;j<margin;j++) printf("   ");
      margin--;
      for(k=0;k<=i;k++)
	{
	  if(i%2){T1=B;T2=A;}
	  else {T1=A;T2=B;}
	  if(k==0||k==i) T1[k]=1;
	  else if(k==1) T1[k]=i;
	  else T1[k]=T2[k-1]+T2[k];
	  printf("%2d    ",T1[k]);
	}
      printf("\n");
    }
}
