#include <stdio.h>
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
  int N,C,I,A[1001],i,j,x,flag;  
  j=0;
  scanf("%d\n",&N);
  while(N--)
    {
      scanf("%d\n",&C);
      scanf("%d\n",&I);
      memset(A,0,sizeof(A));
      j++;
      flag=0;
      for(i=0;i<I;i++)
	{
	  scanf("%d",&x);
	  if(flag||(x>=C)) continue;
	  if(A[C-x])
	    {
	      cout <<"Case #"<<j<<": "<<A[C-x]<<" "<<i+1<<endl;
	      flag=1;
	    }
	  else if(!A[x])A[x]=i+1;
	}
    }
  return 0;
}

