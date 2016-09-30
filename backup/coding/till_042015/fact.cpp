#include <iostream>
using namespace std;

void fact(int n)
{
	long x,carry;
	int A[200]={0};
	A[199]=1;
	int i,j,k;
	k=199;
	for(i=2;i<=n;i++)
	{
		carry=0;
		for(j=199;j>=k;j--)
		{
			x=A[j]*i+carry;
			A[j]=x%10;
			carry=x/10;
		}
		while(carry)
		{
			k--;	
			A[k]=carry%10;
			carry=carry/10;
		
		}		
	}
	for(i=k;i<200;i++)	cout<< A[i];
	cout << endl;		
}


int main()
{
	// int t,n;
	// cin>>t;
	// while(t--)
	// {
	// 	cin >>n;
	// 	fact(n);			
	// }
  fact(7);
	return 0;
}
