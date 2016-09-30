#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
void keypad_words(long n);
void All_strings_space_separated(char *str);
int main()
{

  All_strings_space_separated("abcd");
  return 0;
}

void f(char *s, char * output, int i, int j)
{
  if(s[i+1]=='\0')
    {
      output[j]=s[i];
      output[j+1]='\0';
      printf("%s\n",output);
    }
  else
    {
      output[j]=s[i];
      output[j+1]=' ';
      f(s,output,i+1,j+2);
      f(s,output,i+1,j+1);
    }

}

void All_strings_space_separated(char *str)
{
  char *output;
  int len;
  if(str && str[0])
    {
      len=strlen(str);
      output=(char*)malloc(2*len+1);
      memset(output,0,2*len+1);
      f(str,output,0,0);
    }
}
int print_words(long n, char P[], int k, int r)
{
  int i;
  long d,z;
  if(n==0){P[k]='\0';printf("%s\n",P);}
  else
    {
      //z=pow(10,r-k-1); uncomment while running this function.
      d=n/z;
      n=n%z;
      for(i=0;i<3;i++)
	{
	  if(d<7) P[k]=91+3*d+i;
	  else P[k]=92+3*d+i;
	  print_words(n,P,k+1,r);
	  if((d==7 || d==9)&&(i==2)) {P[k]=93+3*d+i;print_words(n,P,k+1,r);}	  
	}
    }
}


void keypad_words(long n)
{
  int i;
  char *P;
  long m;
  m=n;
  for(i=0;m;i++) m/=10;
  P=(char*)malloc(i+1);
  memset(P,0,i+1);
  print_words(n,P,0,i);
}

