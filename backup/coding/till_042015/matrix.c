#include <stdio.h>
#include <limits.h>


#define N 5
#define K 3
#define ROW 4
#define COL 4
int isSafe(int (*M)[COL],int i,int j);
void _8Queen(int (*M)[COL], int q);
void KnightTour(int (*M)[COL],int i, int j);
int ExtractMin_YoungTableau(int M[][COL]);
void YT1(int M[][COL], int i, int j);
void YT(int M[][COL], int i, int j);
void YT3(int M[][COL], int i, int j);
void K_matrix(int A[][N], int B[][K]);
void print_matrix(int M[][COL]);
void print_Char_matrix(char M[][COL]);
void Rotate_90(int M[][COL]);
void Spiral_print(int M[][COL]);
int Kadane_MaxSumSubarray(int A[], int n, int *l, int *r);
int Max_SumSubmatrix(int M[][COL]);
int maximum_1s(int M[][COL]);
void Find_string(char M[][COL], char *str );
void flip_bounded_0_by_1(char (*M)[COL]);
void flood_fill(char (*M)[COL], int i, int j, char c);
void spiral_print(int (*M)[COL]);
void spiral_traversal(int (*M)[COL]);

void rotate_90(int (*M)[COL])
{
  int start, end, k, t1, t2, t3, t4;
  start=0,end=COL-1; 
  while(start<end)
    {
      for(k=0;k<end-start;k++)
	{
	  t1=M[start][start+k];
	  t2=M[start+k][end];
	  t3=M[end][end-k];
	  t4=M[end-k][start];
	  M[start][start+k]=t4;
	  M[start+k][end]=t1;
	  M[end][end-k]=t2;
	  M[end-k][start]=t3;
	}
      start++,end--;
    }
}
int main()
{
  int arr[]={0,0,0,0,0,1,1,1,1,1,1},max;
  //char Mat[ROW][COL]={{'1','1','1','1','1','1','1','1'},{'1','1','1','1','1','1','0','0'},{'1','0','0','1','1','0','1','1'},{'1','2','2','2','2','0','1','0'},{'1','1','1','2','2','0','1','0'},{'1','1','1','2','2','2','2','0'},{'1','1','1','1','1','2','1','1'},{'1','1','1','1','1','2','2','1'}};
  int i,j;
  int M[ROW][COL]={{0},{0},{0},{0}};
 
  //int M[ROW][COL]={{10,20,30,40,50},{12,22,32,42,52},{14,24,34,44,54},{16,26,36,46,56},{18,28,38,48,58}};
  int A[N][N]={1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5};
  int B[K][K]={0};
  //char M[ROW][COL]={"vikas","kumar","pndey","daihr","sroti","chatr"};
  /* print_Char_matrix(Mat); */
  /* printf("\n"); */
  /* flood_fill(Mat,4,4,'3'); */
  /* print_Char_matrix(Mat); */
  /* for(i=0;i<ROW;i++) */
  /*   printf("%s\n",M[i]);     */

  /* Find_string(M,"hridas"); */
  
  //printf("%d\n",maximum_1s(Mat));
  /* Max_SumSubmatrix(Mat); */
  /* max=Kadane_MaxSumSubarray(arr,5,&i,&j); */
  /* printf("%d,%d:%d\n",i,j,max); */
  //_8Queen(M,1);
  //M[0][0]=1;
  /* print_matrix(M); */
  /* printf("\n"); */
  /* rotate_90(M); */
  /* print_matrix(M); */
  /* printf("\n"); */

  /* printf("\n"); */
  //Spiral_print(M);
  //printf("\n");
  // Rotate_90(M);
  //print_matrix(M);
  for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++)
  	M[i][j]=-1;
  }
  /*   printf("\n");} */
  /* for(i=0;i<16;i++) */
  /*   printf("%d\n", ExtractMin_YoungTableau(M)); */
  KnightTour(M,0,0);
  //K_matrix(A,B);
  
  return 0;
}

void spiral_traversal(int (*M)[COL])
{
  int i,j,rs,re,cs,ce;
  rs=cs=0;
  re=ROW-1;ce=COL-1;
  while(rs<re && cs<ce)
    {
      for(j=cs;j<ce;j++) printf("%d ",M[rs][j]);
      for(i=rs;i<re;i++) printf("%d ",M[i][ce]);
      for(j=ce;j>cs;j--) printf("%d ",M[re][j]);
      for(i=re;i>rs;i--) printf("%d ",M[i][cs]);
      rs++,cs++,re--,ce--;
    }
  if(rs==re && cs<ce) for(j=cs;j<=ce;j++)  printf("%d ",M[rs][j]);
  if(cs==ce && rs<=re) for(i=rs;i<=re;i++)  printf("%d ",M[i][cs]);
}


void spiral_print(int (*M)[COL])
{
  int Rstart,Rend,Cstart,Cend,i,j;
  Rstart=0,Rend=ROW-1,Cstart=0,Cend=COL-1;
  while(Rstart<Rend && Cstart<Cend)
    {
      for(j=Cstart;j<Cend;j++) printf("%d ",M[Rstart][j]);
      for(i=Rstart;i<Rend;i++) printf("%d ",M[i][Cend]);
      for(j=Cend;j>Cstart;j--) printf("%d ",M[Rend][j]);
      for(i=Rend;i>Rstart;i--) printf("%d ",M[i][Cstart]);
      Rstart++,Rend--;Cstart++,Cend--;
    }
  if(Rstart==Rend) for(j=Cstart;j<=Cend;j++) printf("%d ",M[Rstart][j]);
  else if(Cstart==Cend) for(i=Rstart;i<Rend;i++) printf("%d ",M[i][Cstart]);
  else{}
}
void flood_fill(char (*M)[COL], int i, int j, char c)
{
  if(i>=0 && i<ROW && j>=0 && j<COL && M[i][j]!=c)
    {
      char t=M[i][j];
      M[i][j]=c;
      if(i-1>=0 && M[i-1][j]==t) flood_fill(M,i-1,j,c);
      if(i+1<ROW && M[i+1][j]==t) flood_fill(M,i+1,j,c);
      if(j-1>=0 && M[i][j-1]==t) flood_fill(M,i,j-1,c);
      if(j+1>=0 && M[i][j+1]==t) flood_fill(M,i,j+1,c);
    }

}

int f(char (*M)[COL], int i, int j)
{
  int u=1,v=1,w=1,x=1;
  if(i==0 || i==ROW-1 || j==0 || j==COL-1) {M[i][j]='2';return 0;}
  M[i][j]='3';

  if(i-1>=0 && M[i-1][j]=='0') u=f(M, i-1, j);
  if(i+1<=ROW-1 && M[i+1][j]=='0') v=f(M, i+1, j);
  if(j-1>=0 && M[i][j-1]=='0') w=f(M, i, j-1);
  if(j+1<=COL-1 && M[i][j+1]=='0') x=f(M, i, j+1);
  if(u && v && w && x) return 1;
  else { M[i][j]='2'; return 0;}

}
void flip_bounded_0_by_1(char (*M)[COL])
{
  int i, j;
  for(i=1;i<ROW-1;i++)    
    for(j=1;j<COL-1;j++)
      if(M[i][j]=='0') f(M,i,j);
  
  for(i=0;i<=ROW-1;i++)    
    for(j=0;j<=COL-1;j++){
      if(M[i][j]=='2') M[i][j]='0';
      else if(M[i][j]=='3') M[i][j]='1';
    }
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
      //return 0;
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
	      printf("%d,%d\n",i,j);
	      break;
	    }
	}
      if(j<COL) break;
    }
  if(i==ROW || j==COL ) printf("-1,-1\n");
}


int binary_search(int A[COL],int s, int e)
{
  if(s<=e)
    {
      if(A[s]) return s;
      else return binary_search__for_leftmost_1(A,s+1,e);
    }
  return -1;
}
int binary_search__for_leftmost_1(int A[COL],int s, int e)
{
  int mid;
  if(s<=e)
    {
      mid=s+(e-s)/2;
      if(!A[mid]) return binary_search__for_leftmost_1(A,mid+1,e);
      else if(!A[mid-1]) return mid;
      else return binary_search__for_leftmost_1(A,s,mid-1);
    }
  return -1;
}
int maximum_1s(int M[][COL])
{
  int k,i;
  if(M)
    {
      k=COL;
      for(i=0;i<ROW;i++)
	{
	  if(k==0) break;
	  if(M[i][k-1]) k=binary_search(M[i],0,k-1);
	}
      return (COL-k);
    }
}




int Max_SumSubmatrix(int M[][COL])
{
  int i,j,k,l,r,L,R,U,D,max,sum,A[COL];
  max=0;
  for(i=0;i<ROW;i++)
    {
      for(k=0;k<COL;k++) A[k]=0;
      for(j=i;j<ROW;j++)
	{
	  for(k=0;k<COL;k++) A[k]+=M[j][k];
	  sum=Kadane_MaxSumSubarray(A,COL,&l,&r);
	  if(i==1&&j==3)
	    {	   
	      printf("%d,%d,%d\n",sum,l,r);
	      for(k=0;k<COL;k++)	      printf("%d ",A[k]);
	    }
	  if(max<sum) {max=sum,L=l,R=r,U=i,D=j;}
	}
    }
  printf("\nr1=%d,r2=%d,c1=%d,c2=%d,Max=%d\n",U,D,L,R,max);
}
int Kadane_MaxSumSubarray(int A[], int n, int *l, int *r)
{
  int i,j,sum,a,b,max;
  if(n>0)
    {
      i=j=a=b=-1;sum=max=0;
      for(j=0;j<n;j++)
	{
	  sum+=A[j];
	  if(sum<0) {i=j+1;sum=0;}
	  else if(sum>max){a=i;b=j;max=sum;}
	}
      *l=a,*r=b;
      return max;
    }
}
void Spiral_print(int M[][COL])
{
  int i,j,r,c;
  r=0,c=COL-1;
  while(r<=(ROW-1)/2 && c>=COL/2)
    {
      for(j=r;j<c;j++) printf("%d ",M[r][j]);
      for(i=r;i<ROW-1-r;i++) printf("%d ",M[i][c]);
      for(j=c;j>r;j--) printf("%d ",M[ROW-1-r][j]);
      for(i=ROW-1-r;i>r;i--) printf("%d ",M[i][r]);
      r++;c--;
    }
}
void Rotate_90(int M[][COL])
{
  int temp,top,bot,i1,i2,i3,i4,j1,j2,j3,j4,r;
  top=0;bot=COL-1;
  while(top<bot)
    {
      i1=top,j1=top,i2=top,j2=bot,i3=bot,j3=bot,i4=bot,j4=top;
      r=0;
      while(r<bot-top)
	{
	  temp=M[i1][j1];
	  M[i1][j1]=M[i4][j4];
	  M[i4][j4]=M[i3][j3];
	  M[i3][j3]=M[i2][j2];
	  M[i2][j2]=temp;
	  j1++,i2++,j3--,i4--,r++;
	}
      top++,bot--;
    }
}
void K_matrix(int A[][N], int B[][K])
{
  int i, j, r, c;
  for(i=0;i<K;i++)    
    for(j=0;j<K;j++)
      B[i][j]=0;
    
  for(i=0;i<=N-K;i++)
    for(j=0;j<=N-K;j++) B[0][0]+=A[i][j];

  for(c=1;c<K;c++)
    {
      B[0][c]=B[0][c-1];
      for(r=0;r<K;r++) B[0][c]=B[0][c]-A[r][c-1]+A[r][N-K+c];
    }
  for(r=1;r<K;r++)
    {
      for(c=0;c<K;c++)
	{
	  B[r][c]=B[r-1][c];
	  for(j=c;j<=N-K+c;j++) B[r][c]=B[r][c]-A[r-1][j]+A[r+N-K][j];
	}
    }
  for(i=0;i<K;i++)
    {
      for(j=0;j<K;j++)
	printf("%d  ",B[i][j]);
      printf("\n");
    }
}



int ExtractMin_YoungTableau(int M[][COL])
{
  int ret,i,j;
  ret=M[0][0];
  M[0][0]=INT_MAX;
  YT3(M,0,0);

  return ret;
}
void print_Char_matrix(char M[][COL])
{
  int i,j;
  for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++)
  	printf("%c ",M[i][j]);
    printf("\n");}
}

void print_matrix(int M[][COL])
{
  int i,j;
  for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++)
  	printf("%d ",M[i][j]);
    printf("\n");}
}
void YT1(int M[][COL], int i, int j)
{
  if(i<ROW-1 || j<COL-1)
    {



      if((i==ROW-1) || (M[i+1][j]>=M[i][j+1]))
	{
	  //printf("j=%d::%d\n",j+1,M[i][j+1]);
	  if(j<COL-1){
	  M[i][j]=M[i][j+1];
	  M[i][j+1]=INT_MAX;
	  YT1(M,i,j+1);}
	}
      else if((j==COL-1) ||(M[i+1][j]<M[i][j+1]))
	{
	  //printf("i=%d::%d\n",i,M[i+1][j]);
	  if(i<ROW-1){
	  M[i][j]=M[i+1][j];
	  M[i+1][j]=INT_MAX;
	  YT1(M,i+1,j);}

	}
    }
}
void YT(int M[][COL], int i, int j)
{
  //  if(!(i+1==ROW && j+1==COL))//&&(M[i+1][j]!=INT_MAX) &&(M[i][j+1]!=INT_MAX))
    //{
      
      if((i+1==ROW)||(M[i][j+1]<=M[i+1][j]))
	{
	  if(j+1<COL){
	  M[i][j]=M[i][j+1];
	  M[i][j+1]=INT_MAX;
	  YT(M,i,j+1);}
	}
      else if((j+1==COL)||(M[i+1][j]<=M[i][j+1]))
	{
	  if(i+1<ROW){
	  M[i][j]=M[i+1][j];
	  M[i+1][j]=INT_MAX;
	  YT(M,i+1,j);}
	}
      else printf("Mistakes\n");
      //}
}

void YT3(int M[][COL], int i, int j)
{
  if((i==ROW-1 && j<COL-1)||(i<ROW-1 && j<COL-1 && M[i][j+1]<=M[i+1][j]))
    {
      M[i][j]=M[i][j+1];
      M[i][j+1]=INT_MAX;
      YT3(M,i,j+1);      
    }
  else if((i<ROW-1 && j==COL-1)||(i<ROW-1 && j<COL-1 && M[i][j+1]>M[i+1][j]))
    {
      M[i][j]=M[i+1][j];
      M[i+1][j]=INT_MAX;
      YT(M,i+1,j);
    }
}

void KnightTour(int (*M)[COL],int i, int j)
{
  int r,c;
  if(M[i][j]==COL*COL) 
    {
      for(i=0;i<COL;i++)
	{
	  for(j=0;j<COL;j++)	  
	    if(M[i][j]/10)  printf("%d ",M[i][j]);
	    else printf("%d  ",M[i][j]);
	  printf("\n");
	}
      printf("\n");
    }
  else
    {
      r=i-1;c=j+2;
      if((r>=0 && c<COL)&&(M[r][c]==0))
	{
	  M[r][c]=M[i][j]+1;
	  KnightTour(M,r,c);
	  M[r][c]=0;
	}
      r=i-2;c=j+1;
      if((r>=0 && c<COL)&&(M[r][c]==0))
	{
	  M[r][c]=M[i][j]+1;
	  KnightTour(M,r,c);
	  M[r][c]=0;
	}

      r=i-2;c=j-1;
      if((r>=0 && c>=0)&&(M[r][c]==0))
	{
	  M[r][c]=M[i][j]+1;
	  KnightTour(M,r,c);
	  M[r][c]=0;
	}

      r=i-1;c=j-2;
      if((r>=0 && c>=0)&&(M[r][c]==0))
	{
	  M[r][c]=M[i][j]+1;
	  KnightTour(M,r,c);
	  M[r][c]=0;
	}

      r=i+1;c=j-2;
      if((r<COL && c>=0)&&(M[r][c]==0))
	{
	  M[r][c]=M[i][j]+1;
	  KnightTour(M,r,c);
	  M[r][c]=0;
	}

      r=i+2;c=j-1;
      if((r<COL && c>=0)&&(M[r][c]==0))
	{
	  M[r][c]=M[i][j]+1;
	  KnightTour(M,r,c);
	  M[r][c]=0;
	}

      r=i+2;c=j+1;
      if((r<COL && c<COL)&&(M[r][c]==0))
	{
	  M[r][c]=M[i][j]+1;
	  KnightTour(M,r,c);
	  M[r][c]=0;
	}

      r=i+1;c=j+2;
      if((r<COL && c<COL)&&(M[r][c]==0))
	{
	  M[r][c]=M[i][j]+1;
	  KnightTour(M,r,c);
	  M[r][c]=0;
	}
    }
}



void _8Queen(int (*M)[COL], int q)
{
  int i,j;
  if(q>COL)
    {
      for(i=0;i<COL;i++)
	{
	  for(j=0;j<COL;j++)	  
	    if(M[i][j])  printf("%d ",M[i][j]);
	    else printf(". ");
	  printf("\n");
	}
      printf("\n");
    }
  else
    {
      for(i=0;i<COL;i++)
	{
	  if(isSafe(M,i,q-1))
	    {
	      M[i][q-1]=q;
	      _8Queen(M,q+1);
	      M[i][q-1]=0;
	    }
	}
    }
}

int isSafe(int (*M)[COL],int i,int j)
{
  int r, c;
  for(c=j-1;c>=0;c--) if(M[i][c]) return 0;

  for(r=i-1,c=j-1;r>=0&&c>=0;r--,c--) if(M[r][c]) return 0;

  for(r=i+1,c=j-1;r<COL&&c>=0;r++,c--) if(M[r][c]) return 0;

  return 1;

}
