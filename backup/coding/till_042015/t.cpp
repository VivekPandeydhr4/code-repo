#include <stdio.h>
#include <string.h>
#include <cmath>
#include <iostream>

#define ROW 6
#define COL 5
using namespace std;
void Find_string(char M[][COL], char *str );
int main()
{
  long long x=(long long)(5*(long long)7778742049*(long long)7778742049) -4;
  //  long long y=5*7778742049*7778742049 +4;
  cout << sqrt(x)<<endl;
  ///cout << sqrt(y)<<endl;
  // long long a=0,b=1,t;
  // //printf("%d\n",sizeof(long ));
  // while(b<7778742049)
  //   {
  //     t=a+b;
  //     a=b;
  //     b=t;
  //     //      printf("%ld\n",b);
  //   }
  // if(b==7778742049) printf("Fibo\n");
  // else printf("NotFibo\n");
  return 0;
}
  /* int i,j;
  char M[ROW][COL]={"vikas","kumar","pndey","daihr","sroti","chatr"};

  printf("%d\n",-10%7);
   
  for(i=0;i<ROW;i++)
    {  for(j=0;j<COL;j++)
        printf("%c",M[i][j]);
      printf("\n");
    }
  Find_string(M,"hridas");
  printf("\n");

  return 0;
}


int search(char M[][COL], char* str, int i, int j, int *r, int *c)
{
  int k;
  if(i>=0 && i<ROW && j>=0 && j<COL){
    if(!str[0]) return 1;
    if(M[i][j]==str[0])
      {
	M[i][j]='\0';
	for(k=0;k<8;k++)
	  {
	    if(search(M, str+1, i+r[k],j+c[k],r,c)) {M[i][j]=str[0];return 1;}
	  }
	M[i][j]=str[0];
      }
  }
  return 0;

}

void Find_string(char M[][COL], char *str )
{
  int  i,j;
  int r[8]={-1,-1,0,1,1,1,0,-1};
  int c[8]={0,1,1,1,0,-1,-1,-1};
  for(i=0;i<ROW;i++)
    {
      for(j=0;j<COL;j++)
        {
          if(search(M,str,i,j,r,c))
            {
              printf("Position of \"%s\":(%d,%d)\n",str,i,j);
              break;
            }
        }
      if(j<COL) break;
    }
  if(i==ROW || j==COL ) printf("-1,-1\n");
}
  */
