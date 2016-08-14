#include "array.h"
#include "list.h"
#include "string.h"

char *chr[10]; 

void phone_digits (int num, char *str)
{
  int r1=0, r2=0, n=0;
  int i=0;
  n = num;
  while (n >= 10)
    {
      if (i) i = i*10;
      else i++;

      r1 = n%10;
      n = n/10;
      r2 = r1*i+r2;
    }
  for (i=0; chr[n][i]; i++)
    {
      int len=strlen (str);
      str[len++] = chr[n][i];
      str[len] = '\0';
      if (r2==0)
	printf("%s ", str);
      phone_digits (r2, str);
      str[len-1] = '\0';
    }
}

int main()
{
  chr[0] = "\0"; chr[2] = "abc"; chr[3] = "def"; chr[4] = "ghi"; 
  chr[5] = "jkl"; chr[6] = "mno"; chr[7] = "pqrs"; chr[8] = "tuv";
  chr[9] = "wxyz"; chr[1] = "\0";

  char str[]="";
  int i;

  for (i=2; i<10; i++)
    printf("%s\n", chr[i]);
  printf("\n");
  int num=2345;

  phone_digits(num, str);
  
  printf("\n");
  return 0;
}
