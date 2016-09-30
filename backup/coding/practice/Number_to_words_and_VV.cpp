#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const char* ONES[]={"One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Ninteen"};
const char *TENS[]={"Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninty"};
const char *BIGS[]={"Hundred","ThousAnd","Lakh","Crore","Billion"};
int size1=19,size2=8,size3=5;
char* Token(const char *str, int *start, int end)
{
  char *T=NULL,i,j;
  if(*start>=end) return NULL;
  T=(char*)malloc(10*sizeof(char));
  for(j=0,i=*start;str[i]&& str[i]!=',' && str[i]!=' ';i++)
    T[j++]=str[i];
  T[j]='\0';
  if(str[i]) i++;
  *start=i;
  return T;
}
int evaluate_segment(const char* str,int end)
{
  char *T=NULL;
  int b=0,x=0,p;

  T=Token(str,&b,end);
  if(!T) return 0;
  
  x=0;
  for(p=0;p<size2;p++)
    {
      if(!strcmp(T,TENS[p]))
	{
	  x=(p+2)*10; break;
	}
    }

  if(p<size2) {T=Token(str,&b,end);if(!T) return x;}
  
  for(p=0;p<size1;p++)
    {
      if(!strcmp(T,ONES[p]))
	{
	  x+=(p+1);
	  break;
	}
    }

  while(T=Token(str,&b,end))
    {
      for(p=0;p<size3;p++)
	{
	  if(!strcmp(T,BIGS[p]))
	    {
	      switch(p)
		{
		case 0: x=x*100;break;
		case 1: x=x*1000;break;
		case 2: x=x*100000;break;
		case 3: x=x*10000000;break;
		case 4: x=x*1000000000;break;
		}
	      break;
	    }
	}
    }
  return x;
}

int Words_to_number(const char *str)
{// Input consist of segments.Each segment is either comma separated or 'and' separated.no more than one spacing between words and space doesnot follow ','. Thousand must be written as ThousAnd and every word starting leteer is capital.

  int n=0,i=0,end;
  end=strlen(str);
  for(i=0;str[i] && str[i]!=',' && (i+3>=end || !(str[i+1]=='a' && str[i+2]=='n' && str[i+3]=='d'));i++) ; 


  if(i!=0) n=evaluate_segment(str,i); 
  if(!str[i]) return n;
  if(str[i]!=',') i=i+4; 
  i++;
  n+=Words_to_number(str+i);
  return n;
}

int main()
{
  int start=0;
  //cout <<evaluate_segment("Five Thousand Hundred Thousand",25)<<endl;
  cout <<Words_to_number("Five ThousAnd Hundred ThousAnd,Two Hundred")<<endl;
  cout <<Words_to_number("Five ThousAnd and Ten")<<endl;
  cout <<Words_to_number("Five ThousAnd,Two Hundred and Forty Five")<<endl;
  return 0;
}
