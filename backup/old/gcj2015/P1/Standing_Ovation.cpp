#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int main()
{
  char shyness[1005]={0};
  int T=0,Case=0,s=0,total=0,require=0,Smax=0;

  scanf("%d",&T);
  while(T--)
    {      
      Case++;
      scanf("%d",&Smax);
      scanf("%s",shyness);
      shyness[Smax+1]='\0';
      for(total=0,require=0,s=0;s<=Smax;s++)
	{
	  if(total+require<s) require+=(s-(total+require));
	  total+=shyness[s]-'0';
	}
      printf("Case #%d: %d\n",Case,require);
    }  
  return 0;
}

