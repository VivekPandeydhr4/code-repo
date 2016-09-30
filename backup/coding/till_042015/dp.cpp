#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define ROW 5
#define COL 4

using namespace std;
/**********************************************************************************/
/* Largest square submatrix of 1's in a given matrix with binary elements */
void LargestSquareSubMatrix(int (*M)[COL])
{
  int i,j,max,max_i,max_j;
  for(i=0;i<ROW;i++)
    {
      for(j=0;j<COL;j++)
	{
	  if(i==0 && j==0) {max=M[i][j];max_i=max_j=0; continue;}
	  if(M[i][j]!=0)
	    {
	      if(i==0 || j==0) M[i][j]=1;
	      else 
		{
		  M[i][j]=M[i-1][j]<M[i][j-1]? M[i-1][j]+1 : M[i][j-1]+1;
		  if(M[i][j]>M[i-1][j-1]+1) M[i][j]=M[i-1][j-1]+1;		  
		}
	      if(M[i][j]>max) {max=M[i][j];max_i=i;max_j=j;}
	    }
	}
    }
  if(max==0) cout << "Not found.\n";
  else  
    {
      cout << "At position: [" <<max_i-max+1 <<"," <<max_j-max+1 <<"]\n";
      cout << "SIZE = " << max << endl;
    } 
}

int Min_Coin_making_change(int D[], int n, int T)
{//Correct but lengthy. See below for easier and space efficient code.
  int i,j,**M;
  M=(int**)malloc((n+1)*sizeof(int*));
  for(i=0;i<=n;i++) M[i]=(int *)malloc((T+1)*sizeof(int));
  for(j=0;j<=T;j++) M[0][j]=-1;
  for(i=0;i<=n;i++) M[i][0]=0;
  sort(D,D+n+1);
  for(i=1;i<=n;i++)
    {
      for(j=1;j<=T;j++)
	{
	  M[i][j]=-1;
	  if(M[i-1][j]!=-1) M[i][j]=M[i-1][j];
	  if(j-D[i-1]>=0 && M[i][j-D[i-1]]!=-1)
	    {
	      if(M[i][j]==-1) M[i][j]=M[i][j-D[i-1]]+1;
	      else M[i][j]= M[i][j-D[i-1]]+1<M[i][j]?M[i][j-D[i-1]]+1:M[i][j];
	    }
	}
    }
  for(i=n;i>=0;i--)
    {
      for(j=0;j<=T;j++)
  	cout << M[i][j]<<" ";
      cout << endl;
    }
  return M[n][T];
}
int Min_Coin_in_Making_Change(int D[], int k, int n)
{
  int i,j,x,*A=(int*)malloc((n+1)*sizeof(int));
  memset(A,-1,(n+1)*sizeof(int));

  A[0]=0;
  for(i=0;i<k;i++)
    {
      for(j=D[i];j<=n;j++)
	{
	  if(A[j]==-1 && A[j-D[i]]!=-1) A[j]=A[j-D[i]]+1;
	  else if(A[j]!=-1 && A[j-D[i]]!=-1) A[j]=(A[j]<=A[j-D[i]]+1) ? A[j] : (A[j-D[i]]+1);
	}
      // for(x=0;x<=n;x++) cout << A[x]<<" ";
      // cout<<endl;
    }
  return A[n];
}
int No_of_ways_making_change(int D[],int k, int n)
{// No. of ways to make total of n from k types of coin of infinite supply
  int i,j,x,*A=(int*)malloc((n+1)*sizeof(int));
  memset(A,0,(n+1)*sizeof(int));
  A[0]=1;
  for(i=0;i<k;i++)
    {
      for(j=D[i];j<=n;j++)
	{
	  A[j]+=A[j-D[i]];
	}
      // for(x=0;x<=n;x++)	  cout<<A[x]<<",";
      // cout<<endl;
    }
  return A[n];
}




// Mobile numeric keypad problem: count the numbers of length N that can be created by pressing left,right,up,down & itself keys
// from a current key. The keypad has only keys 0,1,...9 active.

int Mobile_keypad(int N)
{
  int *A, *B, *t,i,j,sum;
  A=(int*)malloc(10*sizeof(int));
  B=(int*)malloc(10*sizeof(int));
  memset(A,0,10*sizeof(int));
  memset(A,0,10*sizeof(int));

  for(i=1;i<=N;i++)
    {
      for(j=0;j<10;j++)
	{
	  if(i==1) {A[j]=1;continue;}
	  A[j]=B[j];
	  if(j==0) {A[j]+=B[8] ; continue;}
	  if(j!=0 && j!=1 && j!=2 && j!=3) A[j]+=B[j-3];
	  if(j!=0 && j!=1 && j!=4 && j!=7) A[j]+=B[j-1];
	  if(j!=0 && j!=7 && j!=8 && j!=9) A[j]+=B[j+3];
	  if(j!=0 && j!=3 && j!=6 && j!=9) A[j]+=B[j+1];
	  if(j==8) A[j]+=B[0];
	}
      t=A;A=B;B=t;
    }
  for(sum=j=0;j<10;j++) sum+=B[j];
  return sum;
}

int Knapsack_0_1(int W[],int P[], int n, int C)
{// C:capacity, n: no. of items
  int i,j,*Table=(int*)malloc((C+1)*sizeof(int));
  memset(Table,0,(C+1)*sizeof(int));
  for(i=0;i<n;i++)
    {
      for(j=C;j>=W[i];j--)
	{
	  if(Table[j]<Table[j-W[i]]+P[i])
	    Table[j]=Table[j-W[i]]+P[i];
	}
      for(int x=0;x<=C;x++) cout<<Table[x]<<" ";
      cout<<endl;
    }
  
  return Table[C];
}
#define SQUARE(x) (x)*(x)
void word_wrap(const char* s, int width)
{//recheck 
  int *W, *T, *B, l,i,j,k,temp;
  l=strlen(s);
  W=(int*)malloc(l*sizeof(int));
  for(i=k=0;s[i];)
    {
      W[k++]=i;
      while(s[i]&&s[i]!=' ') i++;
      if(!s[i]) W[k]=i;      
      else i++;
    }
  T=(int*)malloc((k+1)*sizeof(int));
  B=(int*)malloc((k+1)*sizeof(int));
  for(i=k-1;i>=0;i--)
    {
      T[i]=SQUARE(width-W[i+1]-W[i])+T[i+1];
      B[i]=i+1;
      for(j=i+1;j<=k;j++)
	{
	  if(W[j]-W[i]>width) break;
	  temp=SQUARE(width-W[j]-W[i])+T[j];
	  if(temp<T[i]) T[i]=temp;B[i]=j;
	}
    }
  cout <<s<<endl;
  for(i=0;i<=k;i++) cout << W[i]<<" ";
  cout <<endl;
  for(i=0;i<=k;i++) cout << T[i]<<" ";
  cout <<endl;
  for(i=0;i<=k;i++) cout << B[i]<<" ";
  cout <<endl;

  j=B[0];
  for(i=0;s[i];i++)
    {
      if(j==-1){cout<<s[i];continue;}
      if(i==W[j]){cout<<endl<<s[i];j=B[j];}
      else cout<<s[i];	
    }
}
int isValidWord(const char **D, int size, char *w)
{
  int i;
  for(i=0;i<size;i++)
    if(!strcmp(D[i],w)) return 1;
  return 0;
}
int word_break(const char *s, const char **D, int size)
{
  int i,n,j,*B;
  char *w;

  n=strlen(s);
  w=(char*)malloc((n+1)*sizeof(char));
  B=(int*)malloc((n+1)*sizeof(int));
  memset(B,0,(n+1)*sizeof(int));
  B[n]=1;

  for(i=n-1;i>=0;i--)
    {
      for(j=i;j<n;j++)
	{
	  strncpy(w,s+i,j-i+1);
	  w[j-i+1]='\0';
	  if(B[j+1] && isValidWord(D,size,w))
	    {
	      B[i]=1;
	      break;
	    }
	}
    }
  cout<<endl;
  return B[0]; 
}

int optimal_game_strategy(int *A, int n)
{// A sequence of coin, two equally smart players choose coins one by one alternately from either side. Maximize sum of first.
  int i,j,l,total,*B,**M;
  B=(int*)malloc(n*sizeof(int));
  M=(int**)malloc(n*sizeof(int*));
  
  for(i=0;i<n;i++) M[i]=(int*)malloc(n*sizeof(int));
  for(B[0]=A[0],i=1;i<n;i++) {B[i]=A[i]+B[i-1];cout<<B[i];}
  for(l=1;l<=n;l++)
    {
      cout <<endl;
      for(i=0;i<=n-l;i++)
	{
	  j=i+l-1;
	  if(i==j) {M[i][j]=A[i];cout<<M[i][j]<<",";continue;}
	  total=B[j];
	  if(i>0) total-=B[i-1];
	  if(total-M[i+1][j]>=total-M[i][j-1]) M[i][j]=total-M[i+1][j];
	  else M[i][j]=total-M[i][j-1];	  
	  cout<<M[i][j]<<",";
	}     
    }
      cout <<endl;
      cout <<endl;
  return M[0][n-1];
}

void Min_Trim(int *A, int n)
{//Trim arrays from either or both sided such that the remaining subarray has property min*2>max.

  int *Min,*Max,i,j,I,J,l;
  Min=(int *)malloc(n*sizeof(int));
  Max=(int *)malloc(n*sizeof(int));
  
  for(i=0;i<n;i++) Min[i]=Max[i]=A[i];
  I=J=0;
  for(l=2;l<=n;l++)
    {
      for(i=0;i<=n-l;i++)
	{
	  j=i+l-1;
	  if(A[j]<Min[i]) Min[i]=A[j];
	  if(A[j]>Max[i]) Max[i]=A[j];
	  if(Min[i]*2>Max[i]) I=i,J=j;
	}
    }
  cout<<I<<","<<J<<","<<endl;
  //printf("%d,%d\n",i,j);
}

int Min_Insert_to_makee_palondrome(const char *s)
{
  int n,i,j,l,**T;
  n=strlen(s);
  T=(int**)malloc(n*sizeof(int*));
  for(i=0;i<n;i++) T[i]=(int*)malloc(n*sizeof(int));
  for(i=0;i<n;i++) T[i][i]=0;

  for(l=2;l<=n;l++)
    {
      for(i=0;i<=n-l;i++)
	{
	  j=i+l-1;
	  if(s[i]==s[j]) T[i][j]=T[i+1][j-1];
	  else
	    {

	      T[i][j]=T[i+1][j]<=T[i][j-1]? (1+T[i+1][j]):(1+T[i][j-1]);
	      //if(M[i][j-1]+1<M[i][j]) M[i][j]=M[i][j-1]+1;
	    }
	}
    }
  return T[0][n-1];
}
/**********************************************************************************************/
int main()
{
  const char *Dict[]={"i","and","like","sam","sung","samsung","mobile","ice","cream","icecream","man","go","mango"};
  int size,D[]={8,15,3,7},E[]={2,2,2,2},F[]={20,30,2,2,2,10};
  int W[]={4,2,3,1,6,4},P[]={6,4,5,3,9,7};
  int A[]={4,5,100,9,10,11,12,15,200};
  size=(sizeof(A)/sizeof(A[0]));

  cout << Min_Insert_to_makee_palondrome("glg")<<endl;
  //Min_Trim(A,size);
  // cout <<optimal_game_strategy(D,4)<<endl;
  // cout <<optimal_game_strategy(E,4)<<endl;
  // cout <<optimal_game_strategy(F,6)<<endl;
  // cout<<word_break("ilikesamsung",Dict,size)<<endl;
  // cout<<word_break("iiiiiiii",Dict,size)<<endl;
  // cout<<word_break("",Dict,size)<<endl;
  // cout<<word_break("ilikelikeimangoiii",Dict,size)<<endl;
  // cout<<word_break("samsungandmango",Dict,size)<<endl;
  // cout<<word_break("samsungandmangok",Dict,size)<<endl;
  // cout<<word_break("ilikeicecreamandmango",Dict,size)<<endl;

  //word_wrap("Geeks for Geeks presents word wrap problem",15);
  //cout<<Knapsack_0_1(W,P,6,10)<<endl;
  //cout << No_of_ways_making_change(D,4,10)<<endl<<endl;
  /*cout<< Mobile_keypad(1)<<endl;
  cout<< Mobile_keypad(2)<<endl;
  cout<< Mobile_keypad(3)<<endl;
  cout<< Mobile_keypad(4)<<endl;
  cout<< Mobile_keypad(5)<<endl;
  cout<< Mobile_keypad(6)<<endl;*/
  // cout << Min_Coin_in_Making_Change(D,3,11)<<endl<<endl;  
  // int i,j,M[ROW][COL];
  // for(i=0;i<ROW;i++)
  //   for(j=0;j<COL;j++)
  //     cin >> M[i][j];
  // LargestSquareSubMatrix(M);

  return 0;
}

////////////////////////////////////////////////////////////////////////////
