#include <stdio.h>
#define COL 8
/****************************************/
void print_matrix(int M[][8])
{
  int i,j;
  for(i=0;i<COL;i++)
    {
      for(j=0;j<COL;j++)
	{
	  if(M[i][j]/10) printf("%d  ",M[i][j]);
	  else printf(" %d  ",M[i][j]);
	}
      printf("\n");
    }
}
int f(int M[][COL], int i, int j, int step)
{
  int r;
  printf("%d\n",step);
  M[i][j]=step;
  if(step==COL*COL)
    {
      print_matrix(M);
      return 1;
    }
  if(i-2>=0 && j+1<COL && M[i-2][j+1]==0) {r=f(M,i-2,j+1,step+1); if(r) return 1;}
  if(i-1>=0 && j+2<COL && M[i-1][j+2]==0) {r=f(M,i-1,j+2,step+1); if(r) return 1;}
  if(i-1>=0 && j-2>=0 && M[i-1][j-2]==0) {r=f(M,i-1,j-2,step+1); if(r) return 1;}
  if(i-2>=0 && j-1>=0 && M[i-2][j-1]==0) {r=f(M,i-2,j-1,step+1); if(r) return 1;}
  if(i+1<COL && j-2>=0 && M[i+1][j-2]==0) {r=f(M,i+1,j-2,step+1); if(r) return 1;}
  if(i+2<COL && j-1>=0 && M[i+2][j-1]==0) {r=f(M,i+2,j-1,step+1); if(r) return 1;}
  if(i+1<COL && j+2<COL && M[i+1][j+2]==0) {r=f(M,i+1,j+2,step+1); if(r) return 1;}
  if(i+2<COL && j+1<COL && M[i+2][j+1]==0) {r=f(M,i+2,j+1,step+1); if(r) return 1;}
  M[i][j]=0;
  return 0;    
}
void Knight_oneTour(int M[][COL])
{
  int i,j,flag;
  for(flag=i=0;i<COL;i++)
    {
      for(j=0;j<COL;j++)
	{
	  if(f(M,i,j,1)){flag=1; break;}
	}
      if(flag) break;
    }
}
/****************************************/
int main()
{

  int M[COL][COL]={0};
  Knight_oneTour(M);
  return 0;
}
