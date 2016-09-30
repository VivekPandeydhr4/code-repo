#include <iostream>
using namespace std;

int main()
{
  int T, N, Q,*A,**M,a,b,i,l,j;
  cin >> T;
  while(T)
    {
      cin >> N;
      A=new int[N];
      M=new int*[N];      
      for(i=0;i<N;i++) {cin >> A[i];M[i]=new int[N-i];}                                
      for(l=1;l<=N;l++)
	{      
	  for(i=0;i<=N-l;i++)
	    {
	      j=i+l-1;
	      if(l==1) M[i][j-i]=A[i];
	      else if(l==2) M[i][j-i]=A[i]^A[j];
	      else M[i][j-i]=M[i+1][j-1-i] ^ A[i] ^A[j];
	    }
	}
      cin >> Q;
      for(i=0;i<Q;i++)
	{
	  cin >> a >> b;            
	  cout << M[a][b] << endl;      
	}
      delete A; 
      for(i=0;i<N;i++)      delete M[i];
      T--;  
    }


  return 0;
}
