#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

void fun(long num, int base, char *tgt)
{
  if(num)
    {
      fun(num/base,base,tgt);
      cout<<tgt[num%base];
    }
}

int main() 
{
  long num=0;
  int t,i,j,k,C=1;
  map<char,int > srcmap;;
  char al[50],src[100],tgt[100];
  cin>>t;
  while(t--)
    {
      scanf("%s %s %s",al,src,tgt);
      for(i=0;src[i];i++) srcmap[src[i]]=i;//.insert(pair<char,int>(src[i],i));
        
      num=0;
      for(k=0;al[k];k++)  num=num*i+srcmap[al[k]];
      cout <<"Case #"<<C++<<": "  ;
      fun(num,strlen(tgt),tgt);
      cout<<endl;
      
    }
  return 0;
}
