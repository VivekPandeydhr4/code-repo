#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
/**************************************/

int No_of_digits(int n)
{
  int count=0,f=0;
  while(n)
    {
      count++;
      if(n%26==0)n--;
      n/=26;
      //if(f==1){n--;f=0;}
    }
  return count;
}
int excel_decoding(char *str)
{
  int sum=0,i;
  for(i=0;str[i];i++)
    {
      sum=sum*26+str[i]-64;
    }
  return sum;
}
char* excel_encoding(int n)
{
char *output,c;
int d,r,index,i,j;
  d=No_of_digits(n);
  output=(char*)malloc((d+1)*sizeof(char));
  memset(output,0,(d+1)*sizeof(char));
  index=0;
  while(n)
    {
      r=n%26;
      switch(r)
	{
        case 0: output[index++]='Z';n--;break;
	default: output[index++]=r+64;
	}
      n=n/26;

    }
for(i=0,j=d-1;i<j;i++,j--)
  {
c=output[i];output[i]=output[j];output[j]=c;
  }
  return output;
}
/**************************************/
int main()
{
  char *input;
  int i;
  for(i=1;i<=100;i++)
    {
      input=excel_encoding(i);
cout << i<<":"<<input<<":"<<excel_decoding(input)<<endl;
      free(input);
    }
  return 0;
}
