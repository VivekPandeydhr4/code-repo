#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;
typedef unsigned long long ULL;//%llu
int main()
{
  int T,Case;
  int l,x;
  char str[10005]={'\0'},I[10005], J[10005], K[10005];

  scanf("%d",&T);
  while(T--)
    {
      Case++;
      memset(I,0,10005);
      memset(J,0,10005);
      memset(K,0,10005);
      scanf("%d",&l,&x);
      scanf("%s",str);
      
      back[0]=str[0];
      for(p=1;p<l;p++)
	{	 
	  sign=back[p-1]<0?-1;1;
	  if(back[p-1]*sign == 1) back[p]=str[p];
	  else back[p]= M[sign*back[p-1]-'i'+1][str[p]-'i'+1] *sign;
	}

      
	 
      for(p=0;p<l*x;p++)
	{
	  c=getProduct(p);
	}
      
    }
  return 0;
}
